#include <string>

class Vertex
{
public:
    Vertex(std::string name, int weight = 1);
    virtual ~Vertex() = default;

    const std::string& name() const { return _name; }
    int weight() const { return _weight; }
protected:
    std::string _name;
    int         _weight;
};

Vertex::Vertex(std::string name, int weight)
    : _name(std::move(name))
    , _weight(weight)
{}