#include "cmfy_output.hpp"

CMFYOutput::CMFYOutput(wlr_output* wlroots_output, CMFYServer* server) :
  wlroots_output{wlroots_output}, server{server}
{}

CMFYOutput::~CMFYOutput() {}
