// Qore Engine written by Adam Weesner @ 2020
#ifndef PLAYER_H
#define PLAYER_H

class Player: public Entity
{
    public:
        Player(): Entity()
        {
        }

        Player(std::string name, Layers layer): Entity(name, layer)
        {
        }

        void OnCollision(const Entity* other) override
        { 
            if (other->layer == ENEMY_LAYER)
            {
                std::cout << "Game over! " << other->name << "\n";
            }
            else if (other->name == "heliport")
            {
                std::cout << "Win! " << other->name << "\n";
            }
        }
};

#endif