# include <spiral_graphics.h>
# include <algorithm>
# include <SDL3/SDL.h>
# include <SDL3_image/SDL_image.h>
# include <iostream>

spiral::Image* spiral::SolidImage (int width, int height, Color color) {
    Color* pixels = new Color[width * height];
    std::fill(pixels, pixels + (width * height), color);
    return new spiral::Image(width, height, pixels);
}

spiral::Image* spiral::LoadFromSource (const char* src) {

    int width;
    int height;
    Color* pixels;

    SDL_Surface* __surface_unformatted = IMG_Load(src);

    if (__surface_unformatted != nullptr) {

        SDL_Surface* __surface = SDL_ConvertSurface(__surface_unformatted, SDL_PIXELFORMAT_ARGB8888);
        
        width = __surface->w;
        height = __surface->h;
        pixels = new spiral::Color[width * height];

        size_t size = __surface->pitch * __surface->h;

        memcpy(pixels, __surface->pixels, size);

        SDL_DestroySurface(__surface);

    }

    else {
        
        std::cout << SDL_GetError() << "\n";

    }

    SDL_DestroySurface(__surface_unformatted);

    return new spiral::Image(width, height, pixels);

}

void spiral::DestroyImage (spiral::Image* img) {
    delete img;
    img = nullptr;
}

spiral::Image** spiral::Subdivide (spiral::Image* src, int& number, int dx, int dy, int col_width, int row_height) {

    int src_height = src->height;
    int src_width = src->width;

    int rows = ((src->height - dy) / row_height) + (((src->height - dy) % row_height) != 0);
    int cols = ((src->width - dx) / col_width) + (((src->width - dx) % col_width) != 0);

    number = rows * cols;

    int start_y = 0;
    int end_y = dy;

    int start_x = 0;
    int end_x = dx;

    int cut_y_positions[rows + 1]{0};
    int cut_x_positions[cols + 1]{0};

    cut_y_positions[0] = 0;
    cut_x_positions[0] = 0;

    for (int i = 0; i <= rows; i++) {
        if (end_y < src->height) {
            cut_y_positions[i] = end_y;
        }
        else {
            cut_y_positions[i] = src->height;
        }
        start_y = end_y;
        end_y += row_height;
    }

    for (int j = 0; j <= cols; j++) {
        if (end_x < src->width) {
            cut_x_positions[j] = end_x;
        }
        else {
            cut_x_positions[j] = src->width;
        }
        start_x = end_x;
        end_x += col_width;
    }

    spiral::Image** subdivisions = new spiral::Image*[rows * cols];

    for (int r = 0; r < rows; r++) {

        for (int c = 0; c < cols; c++) {

            int x1 = cut_x_positions[c];
            int x2 = cut_x_positions[c + 1];

            int y1 = cut_y_positions[r];
            int y2 = cut_y_positions[r + 1];

            int subdv_width = cut_x_positions[c + 1] - cut_x_positions[c];
            int subdv_height = cut_y_positions[r + 1] - cut_y_positions[r];
            spiral::Color* pixels = new spiral::Color[subdv_width * subdv_height];
            
            subdivisions[r * cols + c] = new spiral::Image(subdv_width, subdv_height, pixels);

            for (int i = 0; i < subdv_height; i++) {
                memcpy(
                    subdivisions[r * cols + c]->pixels + (i * subdv_width),
                    src->pixels + src->width * (y1 + i) + x1,
                    subdv_width * sizeof(spiral::Color)
                );
            }

        }

    }

    return subdivisions;

}