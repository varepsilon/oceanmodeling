#include "object.h"
#include "ocean.hpp"

//unsigned Prey::time_to_reproduce_ = DEFAULT_TIME_TO_REPRODUCE;
//
//unsigned Hunter::time_to_reproduce_ = DEFAULT_TIME_TO_REPRODUCE;
//unsigned Hunter::time_to_die_ = DEFAULT_TIME_TO_DIE;

void Prey::Act() {
    Ocean& ocean = Ocean::Instance();
    std::vector< std::pair<int, int> > free_cells;
    Object* up = ocean(x_, y_ + 1);
    Object* down = ocean(x_, y_ - 1);
    Object* left = ocean(x_ - 1, y_);
    Object* right = ocean(x_ + 1, y_);
    if (!up) {
        free_cells.push_back(std::make_pair(x_, y_ + 1));
    }
    if (!down) {
        free_cells.push_back(std::make_pair(x_, y_ - 1));
    }
    if (!left) {
        free_cells.push_back(std::make_pair(x_ - 1, y_));
    }
    if (!right) {
        free_cells.push_back(std::make_pair(x_ + 1, y_));
    }
    if (free_cells.size() == 0) {
        --time_to_reproduce_left_;
        return;
    } else {
        // Pick at random direction (from free cells)
        size_t random_free_cell_index = rand() % free_cells.size();
        if (time_to_reproduce_left_ <= 0) {
            // reproduce itself
            if (ocean.CreateNewObject(PREY,
                    free_cells[random_free_cell_index])) {
                time_to_reproduce_left_ = time_to_reproduce_;
                return;
            } else {
                // continue (move to adjasent cell)
            }
        }
            // go to the adjacent cell
            ocean.MoveObject(this, free_cells[random_free_cell_index]);
            --time_to_reproduce_left_;
            return;
        }
}

void Hunter::Act() {
    Ocean& ocean = Ocean::Instance();

    if (time_to_die_left_ <= 0) {
        ocean.DeleteObject(x_, y_);
        return;
    }

    Object* up = ocean(x_, y_ + 1);
    Object* down = ocean(x_, y_ - 1);
    Object* left = ocean(x_ - 1, y_);
    Object* right = ocean(x_ + 1, y_);

    if (time_to_reproduce_left_ <= 0) {
        std::vector< std::pair<int, int> > free_cells;
        if (!up) {
            free_cells.push_back(std::make_pair(x_, y_ + 1));
        }
        if (!down) {
            free_cells.push_back(std::make_pair(x_, y_ - 1));
        }
        if (!left) {
            free_cells.push_back(std::make_pair(x_ - 1, y_));
        }
        if (!right) {
            free_cells.push_back(std::make_pair(x_ + 1, y_));
        }
        if (free_cells.size() == 0) {
            // continue (may be trying to eat somebody)
        } else {
            size_t random_free_cell_index = rand() % free_cells.size();
            // reproduce itself
            if (ocean.CreateNewObject(HUNTER,
                                      free_cells[random_free_cell_index])) {
                time_to_reproduce_left_ = time_to_reproduce_;
                --time_to_die_left_;
                return;
            } else {
                // continue (may be trying to eat somebody)
            }
        }
    }

    std::vector< std::pair<int, int> > cells;
    std::vector<Object*> objects;

    objects.push_back(up);
    cells.push_back(std::make_pair(x_, y_ + 1));

    objects.push_back(down);
    cells.push_back(std::make_pair(x_, y_ - 1));

    objects.push_back(left);
    cells.push_back(std::make_pair(x_ - 1, y_));

    objects.push_back(right);
    cells.push_back(std::make_pair(x_ + 1, y_));

    size_t random_cell_index = rand() % cells.size();
    // If this cell is free
    if (objects[random_cell_index] == NULL) {
            // Go to the adjacent free cell
            ocean.MoveObject(this, cells[random_cell_index]);
            --time_to_die_left_;
            --time_to_reproduce_left_;
            return;
        }
    else {
        if (Interact(objects[random_cell_index]) == true) {
            // Hunter is happy :)
            time_to_die_left_ = time_to_die_;
        } else {
            --time_to_die_left_;
        }
        --time_to_reproduce_left_;
        return;
    }
}

bool Prey::Dispatch(Hunter& h) {
    Ocean& ocean = Ocean::Instance();
    ocean.DeleteObject(x_, y_);
    return true;
}

bool Prey::Dispatch(Prey& /* p */) {
    return false;
}

bool Hunter::Dispatch(Prey& p ) {
    Ocean& ocean = Ocean::Instance();
    ocean.DeleteObject(p.GetCoords());
    return false;
}

bool Hunter::Dispatch(Hunter& /* h */) {
    return false;
}

bool Obstacle::Dispatch(Prey& /* p */) {
    return false;
}
