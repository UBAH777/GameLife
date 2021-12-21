#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>


Game::Game(Life &life) : Life_ptr(&life) {
    window_size.x = Life_ptr->GetWidth() * cell_size;
    window_size.y = Life_ptr->GetHeight() * cell_size;

    for (auto x = 0; x < life.GetWidth(); ++x) {
        for (auto y = 0; y < life.GetHeight(); ++y) {
            auto tile = new sf::RectangleShape();
            tile->setSize({(float) cell_size, (float) cell_size});
            tile->setFillColor(sf::Color::White);
            tile->setOutlineThickness(1.2f);
            tile->setOutlineColor(sf::Color::Black);
            tile->setPosition(x * cell_size, y * cell_size);
            tilemap.push_back(*tile);
        }
    }
    window.create(sf::VideoMode{(u_int) window_size.x, (u_int) window_size.y}, "Game of Life");

    RenderLoop();
}


void Game::RenderLoop() {
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            DispatchEvent(event);
        }
        for (int y = 0; y < Life_ptr->GetHeight(); ++y) {
            for (int x = 0; x < Life_ptr->GetWidth(); ++x) {
                if (Life_ptr->GetStateCell(x, y)) {
                    tilemap[(y * Life_ptr->GetWidth()) + x].setFillColor(sf::Color::Green);
                } else
                    tilemap[(y * Life_ptr->GetWidth()) + x].setFillColor(sf::Color::White);
            }
        }

        for (auto item : tilemap) {
            window.draw(item);
        }

        sf::sleep(sf::seconds(0.1f));
        window.display();

        if (!is_stopped) Life_ptr->Mutate();
    }
}

void Game::DispatchEvent(sf::Event &event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
        is_stopped = !is_stopped;
    }
    auto mouse_pos = sf::Mouse::getPosition(window);
    auto view = window.getDefaultView();
    auto mouse_world_pos = window.mapPixelToCoords(mouse_pos, view);
    if (event.type == sf::Event::LostFocus) {
        focused = true;
    }

    if (event.type == sf::Event::GainedFocus) {
        focused = false;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R){
        Life_ptr->FillRandomStates();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
        Life_ptr->ClearStates();
    }

    if (!focused) {
        if (mouse_world_pos.x >= 0 && mouse_world_pos.y >= 0 && mouse_world_pos.x < window_size.x && mouse_world_pos.y < window_size.y) {
            window.setTitle("Position: x-> " + std::to_string((int)(mouse_world_pos.x / cell_size)) + " y-> " + std::to_string((int)(mouse_world_pos.y / cell_size)));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                Life_ptr->SetStateAlive((int) (mouse_world_pos.y / cell_size), (int) (mouse_world_pos.x / cell_size));
            }
        }
    }
}

