
#include "editor.h"
#include "kyo/game.h"


Editor::Editor(Game* game): game(game) {

    this->set_name("Editor");

    cursor = spawn_entity<sf::CircleShape>();
    cursor->setFillColor(sf::Color::Transparent);
    cursor->setOutlineColor(sf::Color::Red);
    cursor->setOutlineThickness(2.f);
    cursor->setRadius(10);
    cursor->setOrigin({10, 10});

    font.loadFromFile("FiraCode-VF.ttf");

    info = spawn_entity<sf::Text>();
    info->setFont(font);
    info->setOrigin({-15, 0});
    info->setCharacterSize(14);
}

Editor::~Editor() {

    PRINT("deleting editor");

    delete plat_a;
    PRINT("  deleted plat_a");

    delete plat_b;
    PRINT("  deleted plat_b");
}

void Editor::update(float delta) {

    string msg = (string)this->get_pos() + "\n";

    msg += "TYPE = " + STR(plat_mode) + "\n";

    if(plat_a) {
        msg += "A = " + (string)*plat_a + "\n";
    }

    info->setString(msg);

    cursor->setPosition(get_pos());
    info->setPosition(get_pos());
}

void Editor::key_press(Key key) {

    float speed = EDITOR_GRID;

    if(Keyboard::isKeyPressed(Key::LShift)) {
        speed = speed * 10;
    }

    switch(key) {
    case Key::Left:

        this->move({-speed, 0}); break;

    case Key::Right:

        this->move({speed, 0}); break;

    case Key::Down:

        this->move({0, speed}); break;

    case Key::Up:

        this->move({0, -speed}); break;

    case Key::Return:

        if(!plat_a) { // set first point

            plat_a = new vec2(this->get_pos());
        }
        else if(!plat_b) { // set second point and add platform

            plat_b = new vec2(this->get_pos());

            game->get_level().add_platform(*plat_a, *plat_b, 16, plat_mode);
            delete plat_a; plat_a = NULL;
            delete plat_b; plat_b = NULL;
        }
        break;

    case Key::RShift:

        plat_mode = (plat_mode + 1) % 2; // cycle through 0 and 1

    default: break;
    }
}

