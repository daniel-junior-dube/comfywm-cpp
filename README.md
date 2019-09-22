
Following the tutorial provided by Drew Devault (Warning : Significant changes was made to wlroots since this tutorial) : https://drewdevault.com/2018/02/17/Writing-a-Wayland-compositor-1.html

Inspiration :
- https://github.com/swaywm/wlroots/tree/master/tinywl
- https://github.com/swaywm/sway
- https://github.com/NickSica/ChameleonWM

To compile, run these commands:
    meson build
    ninja -C build
    sudo ninja -C build install
