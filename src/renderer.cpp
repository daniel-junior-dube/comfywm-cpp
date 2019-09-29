#include "renderer.hpp"
#include "view.hpp"
#include "server.hpp"

RenderOutputTransaction::RenderOutputTransaction(CMFYOutput output) :
  output{output}
{
  clock_gettime(CLOCK_MONOTONIC, &this->start_time);
}
RenderOutputTransaction::~RenderOutputTransaction() {}

void RenderOutputTransaction::commit() {
  wlr_output_commit(this->output.wlroots_output);
}

CMFYRenderer::CMFYRenderer(wlr_renderer* wlroots_renderer) :
  wlroots_renderer{wlroots_renderer}
{}

CMFYRenderer::~CMFYRenderer() {}

/*

 */
void CMFYRenderer::render(int width, int height, std::function<void()> callback) {
  wlr_renderer_begin(this->wlroots_renderer, width, height);
  if (this->should_clear) {
    wlr_renderer_clear(this->wlroots_renderer, this->clear_color);
  }
  callback();
  wlr_renderer_end(this->wlroots_renderer);
}

/*

 */
void CMFYRenderer::render_output(CMFYOutput output, std::function<void(RenderOutputTransaction transaction)> callback) {
  this->with_output_attached(output, [&](RenderOutputTransaction transaction) {
    std::pair<int, int> resolution = output.get_effective_resolution();
    this->render(resolution.first, resolution.second, [&]() {
      callback(transaction);
    });
  });
}

/*

 */
void CMFYRenderer::with_output_attached(CMFYOutput output, std::function<void(RenderOutputTransaction transaction)> callback) {
  if (!wlr_output_attach_render(output.wlroots_output, nullptr)) {

    // TODO: <EASY> Log that we failed to attach output to render
    return;
  }
  RenderOutputTransaction transaction = RenderOutputTransaction(output);
  callback(transaction);
  transaction.commit();
}

/*

 */
void CMFYRenderer::draw_surface(wlr_surface *surface, int sx, int sy, void *data) {
  /* This function is called for every surface that needs to be rendered. */
  RenderData* render_data = static_cast<RenderData*>(data);
  CMFYView* view = render_data->view;
  CMFYOutput* output = render_data->output;
  wlr_output* wlroots_output = output->wlroots_output;

  /* We first obtain a wlr_texture, which is a GPU resource. wlroots
   * automatically handles negotiating these with the client. The underlying
   * resource could be an opaque handle passed from the client, or the client
   * could have sent a pixel buffer which we copied to the GPU, or a few other
   * means. You don't have to worry about this, wlroots takes care of it. */
  struct wlr_texture *texture = wlr_surface_get_texture(surface);
  if (!texture) {
    return;
  }

  /* The view has a position in layout coordinates. If you have two displays,
   * one next to the other, both 1080p, a view on the rightmost display might
   * have layout coordinates of 2000,100. We need to translate that to
   * output-local coordinates, or (2000 - 1920). */
  double ox = 0, oy = 0;
  wlr_output_layout_output_coords(view->server->wlroots_output_layout, wlroots_output, &ox, &oy);
  ox += view->x + sx;
  oy += view->y + sy;

  /* We also have to apply the scale factor for HiDPI outputs. This is only
   * part of the puzzle, TinyWL does not fully support HiDPI. */
  struct wlr_box box = {
    ox * wlroots_output->scale,
    oy * wlroots_output->scale,
    surface->current.width * wlroots_output->scale,
    surface->current.height * wlroots_output->scale,
  };

  /*
   * Those familiar with OpenGL are also familiar with the role of matricies
   * in graphics programming. We need to prepare a matrix to render the view
   * with. wlr_matrix_project_box is a helper which takes a box with a desired
   * x, y coordinates, width and height, and an output geometry, then
   * prepares an orthographic projection and multiplies the necessary
   * transforms to produce a model-view-projection matrix.
   *
   * Naturally you can do this any way you like, for example to make a 3D
   * compositor.
   */
  float matrix[9];
  enum wl_output_transform transform = wlr_output_transform_invert(surface->current.transform);
  wlr_matrix_project_box(matrix, &box, transform, 0, wlroots_output->transform_matrix);

  /* This takes our matrix, the texture, and an alpha, and performs the actual
   * rendering on the GPU. */
  wlr_render_texture_with_matrix(render_data->renderer->wlroots_renderer, texture, matrix, 1);

  /* This lets the client know that we've displayed that frame and it can
   * prepare another one now if it likes. */
  wlr_surface_send_frame_done(surface, render_data->when);
}
