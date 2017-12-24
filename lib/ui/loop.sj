loopLastRect := rect()

mainLoop() {
    ticks := 0
    --c--
    sjv_ticks = SDL_GetTicks();
    --c--
    animator.nextFrame(ticks)

    size : rootWindowRenderer.getSize()
    rootScene.setSize(size)
    rootScene.start()
    rect : rect(0, 0, size.w, size.h)
    if loopLastRect != rect {
        root.setRect(rect)
    }
    root.render(rootScene)
    rootScene.end()
    rootWindowRenderer.present()

    --c--
    SDL_Event e;
    while(SDL_PollEvent( &e ) != 0) {
    --c--
        mouse_eventType := empty'mouseEventType
        mouse_x := 0
        mouse_y := 0
        mouse_isLeftDown := false

        --c--
        switch (e.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                sjv_mouse_eventtype.isvalid = true;
                sjv_mouse_eventtype.value = sjv_mouseeventtype_down;
                sjv_mouse_x = e.button.x;
                sjv_mouse_y = e.button.y;
                sjv_mouse_isleftdown = e.button.state & SDL_BUTTON(SDL_BUTTON_LEFT);
                break;
            case SDL_MOUSEBUTTONUP:
                sjv_mouse_eventtype.isvalid = true;
                sjv_mouse_eventtype.value = sjv_mouseeventtype_up;
                sjv_mouse_x = e.button.x;
                sjv_mouse_y = e.button.y;
                sjv_mouse_isleftdown = e.button.state & SDL_BUTTON(SDL_BUTTON_LEFT);
                break;
            case SDL_MOUSEMOTION:
                sjv_mouse_eventtype.isvalid = true;
                sjv_mouse_eventtype.value = sjv_mouseeventtype_move;
                sjv_mouse_x = e.motion.x;
                sjv_mouse_y = e.motion.y;
                sjv_mouse_isleftdown = SDL_GetGlobalMouseState(0, 0) & SDL_BUTTON(SDL_BUTTON_LEFT);
                break;
        }
        --c--

        shouldContinue := true // TODO: should not need this
        ifValid mouse_eventType {
            ifValid m : mouse_captureElement {
                shouldContinue = m.fireMouseEvent(mouseEvent(
                    type : mouse_eventType
                    point : point(mouse_x, mouse_y)
                    isCaptured : true
                    isLeftDown : mouse_isLeftDown
                )) 
                void
            } elseEmpty {
                shouldContinue = root.fireMouseEvent(mouseEvent(
                    type : mouse_eventType
                    point : point(mouse_x, mouse_y)
                    isCaptured : false
                    isLeftDown : mouse_isLeftDown
                )) 
                void
            }
        }
    --c--
    }
    --c--

    void
}

runLoop() {
    --c--
##ifdef EMSCRIPTEN
    emscripten_set_main_loop((em_callback_func)sjf_mainloop, 0, 0);
    exit(0);
##else
    bool quit = false;
    while (!quit) {
        #functionStack(mainLoop)();
    }
##endif 
    --c--
}