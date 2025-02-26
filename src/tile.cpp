#include "tile.hpp"

Tile::Tile() : connection_up(true), connection_down(true), connection_left(true), connection_right(true), is_wall(false), is_valid(true)
{

}

int Tile::GetNumberWalls() const
{
    int num_walls = 4;
    if (this->HasConnectionUp()) num_walls--;
    if (this->HasConnectionDown()) num_walls--;
    if (this->HasConnectionLeft()) num_walls--;
    if (this->HasConnectionRight()) num_walls--;
    return num_walls;
}

void Tile::SetConnectionUp(bool val)
{
    this->connection_up = val;
}

void Tile::SetConnectionDown(bool val)
{
    this->connection_down = val;
}

void Tile::SetConnectionLeft(bool val)
{
    this->connection_left = val;
}

void Tile::SetConnectionRight(bool val)
{
    this->connection_right = val;
}

void Tile::SetIsWall()
{
    this->is_wall = true;
    this->SetConnectionUp(false);
    this->SetConnectionDown(false);
    this->SetConnectionLeft(false);
    this->SetConnectionRight(false);
}

bool Tile::HasConnectionUp() const
{
    return this->connection_up;
}

bool Tile::HasConnectionDown() const
{
    return this->connection_down;
}

bool Tile::HasConnectionLeft() const
{
    return this->connection_left;
}

bool Tile::HasConnectionRight() const
{
    return this->connection_right;
}

bool Tile::IsWall() const
{
    return this->is_wall;
}

bool Tile::IsValid() const
{
    return this->is_valid;
}
