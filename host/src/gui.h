#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

enum KEY { W, A, S, D };

struct Img {
    Img() : img(nullptr), texture(nullptr), pos({ 0, 0, 0, 0 }) {}
    Img(SDL_Renderer *renderer, SDL_Surface *img, const SDL_Rect &pos) :
        img(img), pos(pos) {
        texture = SDL_CreateTextureFromSurface(renderer, img);
    }
    SDL_Surface *img;
    SDL_Texture *texture;
    SDL_Rect pos;
};

class Gui {
public:
    Gui() : gui_active_(true) {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            /* Handle problem */
            std::cerr << SDL_GetError() << "\n";
            gui_active_ = false;
        }
        window_ = SDL_CreateWindow("Window caption", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 852, 480, 0);
        if (window_ == nullptr)
        {
            /* Handle problem */
            std::cerr << SDL_GetError() << "\n";
            SDL_Quit();
            gui_active_ = false;
        }
        renderer_ = SDL_CreateRenderer(window_, -1, 0);
        if (renderer_ == nullptr)
        {
            /* Handle problem */
            std::cerr << SDL_GetError() << "\n";
            SDL_Quit();
            gui_active_ = false;
        }

        unselected_wasd_.resize(4);
        selected_wasd_.resize(4);
        images_.resize(4);

        if (gui_active_) {
            unselected_wasd_[W] = Img(renderer_, SDL_LoadBMP("rss/w_key.bmp"), { 110, 5, 100, 100 });
            unselected_wasd_[A] = Img(renderer_, SDL_LoadBMP("rss/a_key.bmp"), { 5, 110, 100, 100 });
            unselected_wasd_[S] = Img(renderer_, SDL_LoadBMP("rss/s_key.bmp"), { 110, 110, 100, 100 });
            unselected_wasd_[D] = Img(renderer_, SDL_LoadBMP("rss/d_key.bmp"), { 215, 110, 100, 100 });

            selected_wasd_[W] = Img(renderer_, SDL_LoadBMP("rss/selected_w_key.bmp"), { 110, 5, 100, 100 });
            selected_wasd_[A] = Img(renderer_, SDL_LoadBMP("rss/selected_a_key.bmp"), { 5, 110, 100, 100 });
            selected_wasd_[S] = Img(renderer_, SDL_LoadBMP("rss/selected_s_key.bmp"), { 110, 110, 100, 100 });
            selected_wasd_[D] = Img(renderer_, SDL_LoadBMP("rss/selected_d_key.bmp"), { 215, 110, 100, 100 });
        }

        images_[W] = &unselected_wasd_[W];
        images_[A] = &unselected_wasd_[A];
        images_[S] = &unselected_wasd_[S];
        images_[D] = &unselected_wasd_[D];
    }

    ~Gui() {
        if (gui_active_) {
            for (auto &img : unselected_wasd_) {
                SDL_FreeSurface(img.img);
                SDL_DestroyTexture(img.texture);
            }
            for (auto &img : selected_wasd_) {
                SDL_FreeSurface(img.img);
                SDL_DestroyTexture(img.texture);
            }
            SDL_DestroyRenderer(renderer_);
            SDL_DestroyWindow(window_);
            SDL_Quit();
        }
    }

    void renderScreen() {
        if (gui_active_) {
            // Clear the buffer of color, setting it to black
            SDL_RenderClear(renderer_);

            // Copy each image's texture to the renderer
            for (const Img *img : images_) {
                SDL_RenderCopy(renderer_, img->texture, NULL, &(img->pos));
            }

            // Draw the buffer into the window
            SDL_RenderPresent(renderer_);
        }
    }

    void onWPress() { images_[W] = &selected_wasd_[W]; }
    void onWRelease() { images_[W] = &unselected_wasd_[W]; }
    void onAPress() { images_[A] = &selected_wasd_[A]; }
    void onARelease() { images_[A] = &unselected_wasd_[A]; }
    void onSPress() { images_[S] = &selected_wasd_[S]; }
    void onSRelease() { images_[S] = &unselected_wasd_[S]; }
    void onDPress() { images_[D] = &selected_wasd_[D]; }
    void onDRelease() { images_[D] = &unselected_wasd_[D]; }
private:
    SDL_Window *window_;
    SDL_Renderer *renderer_;

    bool gui_active_;
    std::vector<Img> unselected_wasd_;
    std::vector<Img> selected_wasd_;
    std::vector<Img*> images_;
};

#endif