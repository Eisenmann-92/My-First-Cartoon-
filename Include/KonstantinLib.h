//{===========================================================================
//! @brief      Библиотека функций для рисования мультфильма посвященного дню космонавтики.
//!
//!             В рамках КПК по С++ от МФТИ
//!
//! @date       2021
//! @par        Copyright: (C) Константин Проценко <procenkok@yandex.ru>
//! @mainpage
//!             Функции для рисования элементов мультфильма:
//!             - @ref   drawCar();
//!               @image html car.png
//!
//!             - @ref   drawSun();
//!               @image html sun.png
//!
//!             - @ref   drawRain();
//!               @image html rain.png
//!
//!             - @ref   drawPuddle();
//!               @image html puddle.png
//!
//!             - @ref   drawHouse();
//!               @image html house.png
//!
//!             - @ref   drawHouses();
//!               @image html houses.png
//!
//!             - @ref   drawRocket();
//!               @image html rocket.png
//!
//!             - @ref   drawCloud();
//!               @image html cloud.png
//!
//!             - @ref   drawMan( );
//!               @image html man.png
//}===========================================================================

#include "TXLib.h"
#include "config.h"
#include <cstdlib>

//-----------------------------------------------------------------------------
namespace Konstantin
    {
    void drawBackground ();
    void drawStartTitles ();
    void drawEndTitles ();
    void drawSky (int x, int y);
    void drawGround (int x, int y);
    void drawHouses (int t = 0);
    void drawRocket (int x, int y, double sizeX, double sizeY, COLORREF rocket_color, int t);
    void drawRain (int x0, int y0, int sizeY = 10);
    void drawHouse (int x, int y, double sizeX, double sizeY, COLORREF house_color,
                    int roof_h  = 0, int roof_w = 0,
                    int windows = 3, int door   = 0);
    void drawCar (int x, int y, double sizeX, double sizeY, COLORREF car_color,
                  int janitor = 10, double window =  0,
                  double wheel = 0, double lights = 10);
    void drawMan (int x, int y, double sizeX, double sizeY, COLORREF skin_color,
                  double rhand = 0, double lhand = 0,
                  double legs  = 0, double jezl  = 0,
                  double eyes  = 2);
    void drawLightning (int x,  int y,  double sizeX, double sizeY, COLORREF light_color);
    void drawRoof (int x1, int x2, int y, COLORREF roof_color);
    void drawWindows (int x1, int y1, int x2, int y2, int count);
    void drawSun (int x,  int y, int r, int eyes, double koso = 0, int tang = 0);
    void drawCloud (int x,  int y, int r);
    void drawPuddle (int t,  int size);

    //{-----------------------------------------------------------------------------
    //! Рисует стартовые титры
    //!
    //! На экране слева направо происходит движение текста,
    //! скорость движения зависит от константы DELAY
    //!
    //! @note Текст является конкретным для данного мультфильма,
    //!       сменить при необходимости
    //}-----------------------------------------------------------------------------

    void drawStartTitles ()
        {
        int t = 0;

        txSetFillColor (TX_BLACK);
        txSetColor (TX_WHITE);

        while (t <= 85)
            {
            txBegin ();
            txClear ();
            txSelectFont ("TimesNewRoman", 150);
            txTextOut (SCR_WIDTH + 200 - t * 15, 100, "Posvyashchaetsya");

            txSelectFont ("Arial", 130);
            txTextOut (SCR_WIDTH + 500 - t * 18, 250, "Dnyu kosmonavtiki");

            txSleep (100 * DELAY);
            txEnd ();
            t++;
            }

        txSleep (300 * DELAY);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует фон
    //!
    //! Рисует фон в виде синего неба и дороги с разметкой
    //!
    //! @note  Функция вызывает отдельно функцию, которая рисует небо
    //!        и функцию, которая рисует коричневую дорогу с разметкой
    //}-----------------------------------------------------------------------------

    void drawBackground ()
        {
        drawSky (0,   0);
        drawGround (0, 540);
        }
    //{-----------------------------------------------------------------------------
    //! Рисует небо
    //!
    //! На экране происходит прорисовка прямоугольника синего цвета
    //!
    //! @param x  - координата начала рисования неба по оси х
    //! @param y  - координата начала рисования неба по оси y
    //!
    //! @note     Небо рисуется от левой верхней точки (х, у) до
    //!           правой нижней точки (ширина и высота размера экрана)
    //!
    //! @par      Пример использования:
    //! @code
    //!           drawSky (0, 0)
    //! @endcode
    //!
    //! @warning  Рекомендуется использовать именно левый верхний угол для начала прорисовки неба.
    //}-----------------------------------------------------------------------------

    void drawSky (int x, int y)
        {
        txSetFillColor (RGB (0, 0, 128));
        txSetColor (RGB (0, 0, 128));

        txRectangle (x, y, x + SCR_WIDTH, y + SCR_HEIGTH);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует дорогу
    //!
    //! Внизу экрана рисуется коричневая дорога с белой разметкой
    //!
    //! @param x  - координата начала рисования дороги по оси х
    //! @param y  - координата начала рисования дороги по оси y
    //!
    //! @note     Дорога рисуется от левой верхней точки (х, у) до
    //!           правой нижней точки (ширина и высота размера экрана)
    //!
    //! @par      Пример использования:
    //! @code
    //!           drawGround (0, 540);
    //! @endcode
    //}-----------------------------------------------------------------------------

    void drawGround (int x, int y)
        {
        txSetFillColor (RGB (185, 122, 85));
        txSetColor (RGB (185, 122, 85));

        txRectangle (x, y, x + SCR_WIDTH, y + SCR_HEIGTH);

        txSetColor (RGB (255, 255, 255), 3);
        int step = 0;

        for (int i = 1; i <= 10; i++)
            {
            txLine (x + step, y + (SCR_HEIGTH - y) / 2, x + step + (SCR_WIDTH - x) / 10, y + (SCR_HEIGTH - y) / 2);
            step += x + (SCR_WIDTH - x) / 5;
            }
        }

    //{-----------------------------------------------------------------------------
    //! Рисует дождь
    //!
    //! Начиная с указанной координаты и до конца экрана рисуется дождь.
    //! Дождь прорисовывается в виде отдельных линий дождинок.
    //!
    //! @param x0    - координата начала рисования дождя по оси х
    //! @param y0    - координата начала рисования дождя по оси y
    //! @param sizeY - длина капель дождя в пикселях
    //!
    //! @note        Дождь рисуется от левой верхней точки (х0, у0) до
    //!              правой нижней точки (ширина и высота размера экрана)
    //!              При достаточной задержки прорисовки видно движение дождинок.
    //!
    //! @par         Пример использования:
    //! @code
    //!              drawRain (0, 70, 15);
    //! @endcode
    //}-----------------------------------------------------------------------------

    void drawRain (int x0, int y0, int sizeY)
        {
        int t = 1;

        while (t < 15)
            {
            for (int x = x0; x <= SCR_WIDTH; x += 15)
                {
                txSetColor (TX_WHITE);
                txLine (x, t * 50 + x % 2 * 20 + y0, x, t * 50 + x % 2 * 20 + y0 + sizeY);
                }

            txSleep (5 * DELAY);
            t++;
            }
        }

    //{-----------------------------------------------------------------------------
    //! Рисует лужи
    //!
    //! В определенных координатах на дороге рисуются три лужи разного размера.
    //! При продолжительности дождя лужи увеличиваются, затем уменьшаются (высыхают).
    //!
    //! @param t     - время увеличения/уменьшения лужи в размерах
    //!               +t - лужа увеличивается, -t - лужа уменьшается
    //! @param size  - размер лужи в начальный момент
    //!
    //! @note        Лужа рисуется в виде эллипса и может увеличиваться и уменьшаться.
    //!              При уменьшении лужи необходимо задать ее "начальный" размер,
    //!              чтобы она не уменьшилась меньше нуля и эллипс не начался рисовать
    //!              в обратном направлении (позволило не использовать if в функции).
    //!
    //! @par         Пример использования:
    //! @code
    //!              drawPuddle (-2*t, 100);
    //! @endcode
    //}-----------------------------------------------------------------------------

    void drawPuddle (int t, int size)
        {
        txSetFillColor (RGB (150, 210, 235));
        txSetColor (RGB (150, 210, 235));

        txEllipse (SCR_WIDTH - 150, SCR_HEIGTH - 50, SCR_WIDTH - 150 + size + t / 2, SCR_HEIGTH - 50 + size / 2 + t / 4);
        txEllipse (SCR_WIDTH - 450, SCR_HEIGTH - 30, SCR_WIDTH - 450 + size + t / 2, SCR_HEIGTH - 50 + size / 2 + t / 4);
        txEllipse (SCR_WIDTH - 750, SCR_HEIGTH - 60, SCR_WIDTH - 550 + size + t / 2, SCR_HEIGTH - 50 + size / 2 + t / 4);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует дома
    //!
    //! Справа налево расставляется три домика
    //!
    //! @param t  - позволяет имитировать движение крыши, окон, двери
    //!
    //! @note     Дома рисуются в определенных местах на дороге.
    //!           При вызове функции происходит постоянное движение краев крыши,
    //!           добавление и уменьшение ряда окон, движение двери вверх и вниз
    //!
    //! @par      Пример использования:
    //! @code
    //!           drawHouses (10);
    //! @endcode
    //}-----------------------------------------------------------------------------

    void drawHouses (int t)
        {
        drawHouse (840, 280, 1.8, 1.3, TX_BLACK,    10 + t % 10, 10 + t % 10, 3 - t % 2, 10 + t % 10);
        drawHouse (540, 300, 1.3, 1.2, TX_DARKGRAY, 20 + t % 10, -5 + t % 10, 1 + t % 2, 30 + t % 10);
        drawHouse (240, 340, 1,   1,   TX_MAGENTA,  30 + t % 10, 25 + t % 10, 2 + t % 2, 10 + t % 10);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует ракету
    //!
    //! Ракета с надписью и двумя соплами с выходящим из них огнем
    //!
    //! @param x            - координата левого нижнего угла треугольника носа ракеты по оси х
    //! @param y            - координата левого нижнего угла треугольника носа ракеты по оси у
    //! @param sizeX        - регулирует размер ракеты по ширине
    //! @param sizeY        - регулирует размер ракеты по высоте
    //! @param rocket_color - позволяет задавать цвет ракеты
    //! @param t            - позволяет задавать скорость полета ракеты вверх
    //!
    //! @note               Ракета рисуется от левого нижнего угла треугольника носа ракеты
    //!                     из ракеты выходит огонь красно-оранжевого цвета
    //!
    //! @par                Пример использования:
    //! @code
    //!                     drawRocket (150, 500, 0.7, 1, TX_WHITE, 2*t);
    //! @endcode
    //}-----------------------------------------------------------------------------

    void drawRocket (int x, int y, double sizeX, double sizeY, COLORREF rocket_color, int t)
        {
        txSetFillColor (rocket_color);
        txSetColor (rocket_color);
        txRectangle (x, y - t, ROUND (x + 150 * sizeX), ROUND (y + 200 * sizeY - t));

        txSetColor (TX_RED);
        txCircle (x + 75 * sizeX, y + 75 * sizeY - t, 50 * sizeX);

        txSelectFont ("Arial", 30);
        txTextOut (x + 30 * sizeX, y + 150 * sizeY - t, "CCCP");

        POINT trio[] = {{ROUND (x), ROUND (y - t) }, {ROUND (x +  75 * sizeX), ROUND (y - 100 * sizeY - t) },
                {ROUND (x + 150 * sizeX), ROUND (y - t) },
                {ROUND (x), ROUND (y - t) }
            };
        txPolygon (trio, 4);

        POINT ltrio[] = {{ROUND (x - 25 * sizeX), ROUND (y + 300 * sizeY - t) },
                {ROUND (x),            ROUND (y + 200 * sizeY - t) },
                {ROUND (x + 25 * sizeX), ROUND (y + 300 * sizeY - t) },
                {ROUND (x - 25 * sizeX), ROUND (y + 300 * sizeY - t) }
            };
        txPolygon (ltrio, 4);

        POINT rtrio[] = {{ROUND (x + 125 * sizeX), ROUND (y + 300 * sizeY - t) },
                {ROUND (x + 150 * sizeX), ROUND (y + 200 * sizeY - t) },
                {ROUND (x + 175 * sizeX), ROUND (y + 300 * sizeY - t) },
                {ROUND (x + 125 * sizeX), ROUND (y + 300 * sizeY - t) }
            };
        txPolygon (rtrio, 4);

        txSetFillColor (RGB (250, rand() % 150, 20));
        txSetColor (RGB (250, rand() % 150, 20));

        POINT lfire[] = {{ROUND (x - 25 * sizeX), ROUND (y + 301 * sizeY - t) },
                {ROUND (x),            ROUND (y + 450 * sizeY - t) },
                {ROUND (x + 25 * sizeX), ROUND (y + 301 * sizeY - t) },
                {ROUND (x - 25 * sizeX), ROUND (y + 301 * sizeY - t) }
            };
        txPolygon (lfire, 4);

        POINT rfire[] = {{ROUND (x + 125 * sizeX), ROUND (y + 301 * sizeY - t) },
                {ROUND (x + 150 * sizeX), ROUND (y + 450 * sizeY - t) },
                {ROUND (x + 175 * sizeX), ROUND (y + 301 * sizeY - t) },
                {ROUND (x + 125 * sizeX), ROUND (y + 301 * sizeY - t) }
            };
        txPolygon (rfire, 4);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует солнце
    //!
    //! Солнце имеет язык, белые глаза и черные зрачки
    //!
    //! @param x     - координата центра круга солнца по оси х
    //! @param y     - координата центра круга солнца по оси у
    //! @param r     - радиус солнца
    //! @param eyes  - регулирует размер глаз солнца
    //! @param koso  - позволяет задавать движение зрачков в глазу вправо и влево, имитируя косоглазие
    //! @param tong  - позволяет задавать длину высунутого языка у солнца
    //!
    //! @note        Расположение языка и глаз зависят от радиуса солнца
    //!              и рисуются пропорционально ему.
    //!              При использовании функции в цикле с изменение параметров
    //!              глаз и языка происходит их движение.
    //!
    //! @par         Пример использования:
    //! @code
    //!              drawSun (880, 90, 60, t%10 + 10, t%5, t%10 + 5);
    //! @endcode
    //}-----------------------------------------------------------------------------

    void drawSun (int x, int y, int r, int eyes, double koso, int tong)
        {
        txSetFillColor (RGB (255, 255, 25));
        txSetColor (RGB (255, 255, 25), 5);

        txLine (x,           y - 1.5 * r, x,           y + 1.5 * r);
        txLine (x - r,       y - r,       x + r,       y + r);
        txLine (x - r,       y + r,       x + r,       y - r);
        txLine (x - 1.5 * r, y,           x + 1.5 * r, y);

        txCircle (x, y, r);

        txSetFillColor (TX_WHITE);
        txSetColor (TX_WHITE);
        txCircle (x - r / 3, y - r / 3, (r - eyes) / 4);
        txCircle (x + r / 3, y - r / 3, (r + eyes) / 4);

        txSetFillColor (TX_BLACK);
        txSetColor (TX_BLACK);
        txCircle (x + koso - r / 3, y - r / 3, (r - eyes) / 8);
        txCircle (x - koso + r / 3, y - r / 3, (r + eyes) / 8);

        txSetFillColor (TX_RED);
        txSetColor (TX_RED);
        POINT tongue[] = {{x - r / 3, y + r / 3}, {x, y + tong + r / 2},
                {x + r / 3, y + r / 3}, {x - r / 3,  y + r / 3}
            };
        txPolygon (tongue, 4);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует крышу дома
    //!
    //! Треугольная крыша дома
    //!
    //! @param x0          - координата левой нижней точки треугольника крыши по оси х
    //! @param x1          - координата правой нижней точки треугольника крыши по оси х
    //! @param y           - координата низа крыши по оси у
    //! @param roof_color  - регулирует цвет крыши
    //!
    //! @note               Крыша состоит из двух линий составляя треугольный верх
    //!                     без основания. Крыша рисуется путем вызова ее из функции рисования дома.
    //!                     Высота крыши вычисляется делением ее длины пополам
    //!
    //! @par                Пример использования:
    //! @code
    //!                     drawRoof (ROUND(x - roof_w), ROUND(x + (150 + roof_w)*sizeX), ROUND(y + roof_h), house_color);
    //! @endcode
    //!
    //! @warning            Функция рисует только крышу и поэтому вызывается из функции рисования дома.
    //!
    //! @see                drawHouse()
    //}-----------------------------------------------------------------------------

    void drawRoof (int x0, int x1, int y, COLORREF roof_color)
        {
        txSetColor (roof_color, 10);

        txLine (x0, y, x0 + (x1 - x0) / 2, y - 0.5 * (x1 - x0));
        txLine (x0 + (x1 - x0) / 2, y - 0.5 * (x1 - x0), x1, y);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует окна в доме
    //!
    //! Рисуются окна определенного размера в несколько рядов
    //!
    //! @param x0     - координата левой верхней точки окна по оси х
    //! @param y0     - координата левой верхней точки окна по оси у
    //! @param x1     - ширина окна (координата правой нижней точки окна по оси х)
    //! @param y1     - высота окна (координата правой нижней точки окна по оси у)
    //! @param count  - задает количество рядов окон в доме
    //!
    //! @note         Окна рисуются исходя из количества рядов count.
    //!               Каждый ряд состоит из пяти окон, между которыми задается ширина и высота
    //!               с помощью внутренних переменных size_width и size_height.
    //!
    //! @par          Пример использования:
    //! @code
    //!               drawWindows (x, y, ROUND(x + 150*sizeX), ROUND(y + 200*sizeY), windows);
    //! @endcode
    //!
    //! @warning      Функция рисует только окна и поэтому вызывается из функции рисования дома.
    //!
    //! @see          drawHouse()
    //}-----------------------------------------------------------------------------

    void drawWindows (int x0, int y0, int x1, int y1, int count)
        {
        txSetColor (RGB (255, 255, 255), 2);

        int size_width = 10;
        int size_height = 10;

        for (int i = 1; i <= count; i++)
            {
            for (int j = 1; j <= 5; j++)
                {
                txSetFillColor (RGB (255, 240, rand() % 200));
                txRectangle (x0 + size_width,
                             y0 + size_height,
                             x0 + size_width  + (x1 - x0) / 10,
                             y0 + size_height + (y1 - y0) / 10);
                size_width += (x1 - x0) / 5;
                }

            size_width = 10;
            size_height += (y1 - y0) / 6;
            }
        }

    //{-----------------------------------------------------------------------------
    //! Рисует дом
    //!
    //! Прямоугольный дом с окнами, крышей и дверью
    //!
    //! @param x            - координата левой верхней точки дома по оси х
    //! @param y            - координата левой верхней точки дома по оси у
    //! @param sizeX        - изменение размеров ширины дома
    //! @param sizeY        - изменение размеров высоты дома
    //! @param house_color  - задает цвет дома
    //! @param roof_h       - задает левую нижнюю точку, от которой будет рисоваться крыша по оси у
    //! @param roof_w       - задает левую нижнюю точку, от которой будет рисоваться крыша по оси х
    //! @param windows      - задает количество рядов окон в доме
    //! @param door         - задает высоту двери в доме
    //!
    //! @note               Дом рисуется относительно начальных координат.
    //!                     Позволяет менять его цвет, место расположения крыши (ведь крыша может поехать)
    //!                     количество рядов окон в доме.
    //!
    //! @par                Пример использования:
    //! @code
    //!                     drawHouse (840, 280, 1.8, 1.3, TX_BLACK, 10, 10, 3, 10);
    //! @endcode
    //!
    //! @warning            При рисовании крыши и окон вызывает вспомогательные функции.
    //}-----------------------------------------------------------------------------

    void drawHouse (int x, int y, double sizeX, double sizeY, COLORREF house_color,
                    int roof_h, int roof_w, int windows, int door)
        {
        txSetFillColor (house_color);
        txSetColor (house_color);

        txRectangle (x, y, x + 150 * sizeX, y + 200 * sizeY);

        drawRoof (ROUND (x - roof_w), ROUND (x + (150 + roof_w) *sizeX), ROUND (y + roof_h), house_color);

        drawWindows (x, y, ROUND (x + 150 * sizeX), ROUND (y + 200 * sizeY), windows);

        txSetFillColor (RGB (255, 255, 255));
        txSetColor (RGB (255, 255, 255), 2);

        txRectangle (x + 50 * sizeX, y + (100 + door) *sizeY, x + 100 * sizeX, y + 200 * sizeY);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует тучу
    //!
    //! Рисует тучу в виде головы чебурашки:)
    //!
    //! @param x  - координата левого центра круга тучки по оси х
    //! @param y  - координата левого центра круга тучки по оси у
    //! @param r  - радиус кругов тучки
    //!
    //! @note     Туча рисуется с помощью двух кругов расположенных на расстоянии
    //!           и эллипса, соединяющего эти круги вместе.
    //!
    //! @par      Пример использования:
    //! @code
    //!           drawCloud (100, 150, 50);
    //! @endcode
    //}-----------------------------------------------------------------------------


    void drawCloud (int x, int y, int r)
        {
        txSetFillColor (RGB (128, 128, 128));
        txSetColor (RGB (128, 128, 128));

        txCircle (x,       y, r);
        txCircle (x + 2 * r, y, r);
        txEllipse (x,       y - r, x + 2 * r, y + r);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует молнию
    //!
    //! @param x            - координата крайней левой верхней точки молнии по оси х
    //! @param y            - координата крайней левой верхней точки молнии по оси у
    //! @param sizeX        - задает ширину молнии
    //! @param sizeY        - задает высоту молнии
    //! @param light_color  - цвет молнии
    //!
    //! @note               Молния представляет из себя замкнутый полигон.
    //!
    //! @par                Пример использования:
    //! @code
    //!                     drawLightning (60, 175, 0.8, 0.7, TX_WHITE);
    //! @endcode
    //}-----------------------------------------------------------------------------


    void drawLightning (int x, int y, double sizeX, double sizeY, COLORREF light_color)
        {
        txSetFillColor (light_color);
        txSetColor (light_color, 2);

        POINT lightning[] = {{x, y}, {ROUND (x + 50 * sizeX),  ROUND (y - 25 * sizeY) },
                {ROUND (x + 75 * sizeX),  ROUND (y + 10 * sizeY) },
                {ROUND (x + 70 * sizeX),  ROUND (y + 15 * sizeY) },
                {ROUND (x + 100 * sizeX), ROUND (y + 45 * sizeY) },
                {ROUND (x + 90 * sizeX),  ROUND (y + 50 * sizeY) },
                {ROUND (x + 130 * sizeX), ROUND (y + 105 * sizeY) },
                {ROUND (x + 60 * sizeX),  ROUND (y + 60 * sizeY) },
                {ROUND (x + 72 * sizeX),  ROUND (y + 56 * sizeY) },
                {ROUND (x + 30 * sizeX),  ROUND (y + 33 * sizeY) },
                {ROUND (x + 45 * sizeX),  ROUND (y + 25 * sizeY) },
                {x, y}
            };
        txPolygon (lightning, 12);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует машину
    //!
    //! Машина из двух прямоугольников с колесами
    //!
    //! @param x          - координата левой верхней точки машины по оси х
    //! @param y          - координата левой верхней точки машины по оси у
    //! @param sizeX      - изменение размеров ширины машины
    //! @param sizeY      - изменение размеров высоты машины
    //! @param car_color  - задает цвет авто
    //! @param janitor    - сдвиг рисования "дворника" машины (движение)
    //! @param window     - задает степень опускания окна
    //! @param wheel      - высота расположения колес
    //! @param lights     - радиус фар авто
    //!
    //! @note             Автомобиль представляет из себя два прямоугольника.
    //!                   Имеет возможность двигать "дворниками", опускать окно,
    //!                   менять высоту расположения колес и размер фар.
    //!
    //! @par              Пример использования:
    //! @code
    //!                   drawCar (650, 425, 100, 100, TX_ORANGE, 30, 0.1, -0.1, 7);
    //! @endcode
    //!
    //! @warning          При рисовании линии дворника следить, чтобы он не уходил с окна авто.
    //!                   При опускании окна следить, чтобы оно не уходило в дверь.
    //}-----------------------------------------------------------------------------

    void drawCar (int x, int y, double sizeX, double sizeY, COLORREF car_color,
                  int janitor, double window, double wheel, double lights)
        {
        txSetFillColor (car_color);
        txSetColor (car_color, 2);

        txRectangle (x, y, x + 1.7 * sizeX, y + 0.55 * sizeY);
        txRectangle (x - 0.85 * sizeX, y + 0.55 * sizeY, x + 2.55 * sizeX, y + 1.1 * sizeY);

        txSetFillColor (RGB (0, 0, 0));
        txSetColor (RGB (0, 0, 0), 2);

        txCircle (x - 0.425 * sizeX, y + (1.1 + wheel) *sizeY, 0.3 * sizeX);
        txCircle (x + 1.915 * sizeX, y + (1.1 + wheel) *sizeY, 0.3 * sizeX);

        txSetFillColor (RGB (200, 200, 200));
        txSetColor (RGB (200, 200, 200), 2);

        txCircle (x - 0.425 * sizeX, y + (1.1 + wheel) *sizeY, 0.2 * sizeX);
        txCircle (x + 1.915 * sizeX, y + (1.1 + wheel) *sizeY, 0.2 * sizeX);

        txRectangle (x, y + (0.05 + window) *sizeY, x + 1.6 * sizeX, y + 0.55 * sizeY);

        txSetColor (TX_BLACK, 2);
        txLine (x, y + 0.55 * sizeY, x + janitor, y + janitor);

        txSetFillColor (TX_YELLOW);
        txSetColor (TX_YELLOW);

        txCircle (x - 0.85 * sizeX, y + 0.7 * sizeY, lights / 100 * sizeX);

        txSetFillColor (TX_RED);
        txSetColor (TX_RED);

        txCircle (x + 2.55 * sizeX, y + 0.7 * sizeY, lights / 100 * sizeX);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует человечка с волшебной палочкой
    //!
    //! @param x           - координата верхней точки туловища по оси х
    //! @param y           - координата верхней точки туловища по оси у
    //! @param sizeX       - изменение размеров ширины человека
    //! @param sizeY       - изменение размеров высоты человека
    //! @param skin_color  - задает цвет человека
    //! @param rhand       - задает подъем/опускание правой руки
    //! @param lhand       - задает подъем/опускание левой руки
    //! @param legs        - задает сближение и отдаление ног
    //! @param jezl        - задает направление и длину волшебной палочки
    //! @param eyes        - радиус глаз
    //!
    //! @note              Человек представляет из себя прямые линии (руки, ноги, тело)
    //!                    и круглой головой. Он держит в руке волшебную палочку.
    //!                    Может увеличивать глаза, поднимать и опускать руки,
    //!                    сближать и раздвигать ноги.
    //!
    //! @par              Пример использования:
    //! @code
    //!                   drawMan (100, 550, 80, 170, TX_YELLOW, 0.1, 0, -0.2, 0.2);
    //! @endcode
    //}-----------------------------------------------------------------------------

    void drawMan (int x, int y, double sizeX, double sizeY, COLORREF skin_color,
                  double rhand, double lhand, double legs,  double jezl, double eyes)
        {
        txSetColor (skin_color, 2);
        txSetFillColor (skin_color);

        txLine (x, y - 0.35 * sizeY, x, y - 0.7 * sizeY);
        txLine (x, y - 0.35 * sizeY, x - (0.5 + legs / 2) *sizeX, y);
        txLine (x, y - 0.35 * sizeY, x + (0.5 + legs / 2) *sizeX, y);
        txLine (x, y - 0.65 * sizeY, x - sizeX / 2,   y - (0.4 + lhand) *sizeY);
        txLine (x, y - 0.65 * sizeY, x + sizeX / 1.2, y - (0.7 + rhand) *sizeY);

        txCircle (x, y - sizeY + 0.3 * sizeX, 0.3 * sizeX);

        txSetFillColor (TX_BLUE);
        txSetColor (TX_BLUE);
        txCircle (x - sizeX / 7, y - sizeY / 1.2, 2 + eyes);
        txCircle (x + sizeX / 7, y - sizeY / 1.2, 2 + eyes);

        txSetColor (TX_BLACK, 4);

        txLine (x + sizeX / 1.2, y - (0.7 + rhand) * sizeY, x + sizeX / 1.2, y - (0.8 + jezl) *sizeY);
        }

    //{-----------------------------------------------------------------------------
    //! Рисует титры окончания мультфильма
    //!
    //! На экране слева направо происходит движение текста,
    //! скорость движения зависит от константы DELAY
    //!
    //! @note Текст является конкретным для данного мультфильма,
    //!       сменить при необходимости
    //}-----------------------------------------------------------------------------


    void drawEndTitles ()
        {
        int t = 0;

        txSetFillColor (TX_BLACK);
        txSetColor (TX_WHITE);
        txSelectFont ("Arial", 150);

        while (t <= 110)
            {
            txBegin ();
            txClear ();
            txTextOut (SCR_WIDTH + 100 - t * 25, 160, "YURA, my nichego ne zabyli!");

            txSleep (100 * DELAY);
            txEnd ();
            t++;
            }

        txSelectFont ("Arial", 60);
        txTextOut (350, 150, "CREATED BY:");
        txTextOut (280, 300, "Protsenko Konstantin");
        txTextOut (300, 500, "Magnitogorsk 2021");
        txSleep (3000 * DELAY);
        }
    }
//! My library
