#pragma once

class Bird
{
public:
    virtual bool canWalk(char tile) = 0;
};

class Chicken : public Bird
{
public:
    bool canWalk(char tile) override;
};

// TODO

// Implement the Duck class inheriting from Bird

//

// TODO

// Implement the Goose class inheriting from Bird

//