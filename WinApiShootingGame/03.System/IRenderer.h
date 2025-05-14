#pragma once
class IRenderer {
public:
    virtual void Render(HDC hdc) = 0; 
};