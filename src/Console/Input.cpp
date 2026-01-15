#include "Input.h"

#include <conio.h>

#include "Constants.h"

Input InputHandler::getInput() {
    char inp = _getch();

    if (inp == K_ESC)
        return Input::ESCAPE;
    if (inp == K_ENTER)
        return Input::ENTER;
    if (inp == K_W || inp == K_w)
        return Input::UP;
    if (inp == K_A || inp == K_a)
        return Input::LEFT;
    if (inp == K_S || inp == K_s)
        return Input::DOWN;
    if (inp == K_D || inp == K_d)
        return Input::RIGHT;
    if (inp == K_H || inp == K_h)
        return Input::HINT;
    if (inp == K_R || inp == K_r)
        return Input::SHUFFLE;

    return Input::INVALID;
}