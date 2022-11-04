/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Test
*/

#ifndef TEST_HPP
    #define TEST_HPP


    #include <string>
    #include <iostream>
    #include <functional>

class IDrawable {
    public:

        virtual ~IDrawable() = default;

    private:
};

class Drawable : public IDrawable {

    public:

        virtual ~Drawable() = default;

        friend class Window;

};

class ISprite : public IDrawable {

    public:
        virtual ~ISprite() = default;


    private:
        int _nb;
};

class Sprite : public Drawable {

    public:
        Sprite(int nb)
        : _nb(nb)
        {
        }

        ~Sprite() = default;

        friend class Window;

    private:
        int _nb;
};

class IText : public IDrawable{
    public:

        virtual ~IText() = default;

    private:
};

class Text : public IText {
    public:
        Text(std::string str)
        : _str(str)
        {
        }

        ~Text() = default;

        friend class Window;

    private:
        std::string _str;
};

class IWindow {
    public:

        virtual ~IWindow() = default;
        virtual void draw(ISprite &draw) = 0;
        virtual void draw(IText &draw) = 0;

    private:

};

class myWindow {

    public:
        void draw(int drawable)
        {
            std::cout << "sprite" << drawable << std::endl;
        }

        void draw(std::string drawable)
        {
            std::cout << "text" << drawable << std::endl;
        }
};

class Window : public IWindow {
    public:

        Window()
        {
        }

        ~Window()
        {
        }

        void draw(ISprite &drawable)
        {
            _window.draw(static_cast<Sprite &>(drawable)._nb);
        }

        void draw(IText &drawable)
        {
            _window.draw(static_cast<Text &>(drawable)._str);
        }

    private:
        myWindow _window;
};


#endif /* !TEST_HPP */

int main()
{
    Sprite sprt(1);
    Text txt("ahhh");
    Window window;

    window.draw(sprt);
    window.draw(txt);
}

