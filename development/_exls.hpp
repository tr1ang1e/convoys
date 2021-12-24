#pragma once

class BASE
{
  public:
   
    bool* isdtorv;
    
    BASE() = default;
    BASE(bool*);
    
    virtual ~BASE();
};


class CLASS : public BASE
{
  public:

    CLASS() = default;
    CLASS(bool* isdtorv_ar);

    template <typename T>
    void 
    funct(T) = delete;
    
    void funct(const int&);

    ~CLASS() override;

};