#include <iostream>

class Stream
{
public:
    Stream() { std::cout << "Stream()\n"; };
    virtual ~Stream() { std::cout << "~Stream()\n"; };
};

class InStream : public virtual Stream
{
    std::istream &m_in_stream;

public:
    InStream(std::istream &s) : Stream(), m_in_stream(s) { std::cout << "InStream()\n"; }
    ~InStream() { std::cout << "~InStream()\n"; }

    template <class T>
    std::istream &operator>>(T &text)
    {
        m_in_stream >> text;
        return m_in_stream;
    }
};

class OutStream : public virtual Stream
{
    std::ostream &m_out_stream;

public:
    OutStream(std::ostream &s) : Stream(), m_out_stream(s) { std::cout << "OutStream()\n"; }
    ~OutStream() { std::cout << "~OutStream()\n"; }

    template <class T>
    std::ostream &operator<<(T &text)
    {
        m_out_stream << text;
        return m_out_stream;
    }
};

//   InStream->Stream <- OutStream
//   IOStream => InStream, OutStream
// Diamond inheritance - each of parents have a Stream class. Use "virtual" to avoid multiple 
// instances to be created.
class IOStream : public InStream, OutStream
{
public:
    IOStream() : InStream(std::cin), OutStream(std::cout)
    {
        std::cout << "IOStream()\n";
    }

    ~IOStream() { std::cout << "~IOStream()\n"; }

    template <class T>
    IOStream &operator<<(T &text)
    {
        OutStream::operator<<(text);
        return *this;
    }

    template <class T>
    IOStream &operator>>(T &text)
    {
        InStream::operator>>(text);
        return *this;
    }
};

int diamond_inheritance(void)
{
    // std::cout << "Hello!\n";
    std::string data;
    // {
    //     InStream in(std::cin);
    //     OutStream out(std::cout);
    //     out << "Provid data: ";
    //     in >> data;
    //     out << "User data: " << data << std::endl;
    // }

    IOStream io;
    io << "Provid data: ";
    io >> data;
    io << "User data: " << data << "\n"; // std::endl;

    return 0;
}