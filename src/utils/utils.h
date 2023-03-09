#ifndef UTILS_H
#define UTILS_H
#include <QMap>
#include <QtGlobal>
#include <QSize>

namespace KEYBOARD
{
static constexpr const int KEY_0 = 0;
static constexpr const int KEY_1 = 1;
static constexpr const int KEY_2 = 2;
static constexpr const int KEY_3 = 3;
static constexpr const int KEY_4 = 4;
static constexpr const int KEY_5 = 5;
static constexpr const int KEY_6 = 6;
static constexpr const int KEY_7 = 7;
static constexpr const int KEY_8 = 8;
static constexpr const int KEY_9 = 9;

static constexpr const int KEY_Q = 10;
static constexpr const int KEY_W = 11;
static constexpr const int KEY_E = 12;
static constexpr const int KEY_R = 13;
static constexpr const int KEY_T = 14;
static constexpr const int KEY_Y = 15;
static constexpr const int KEY_U = 16;
static constexpr const int KEY_I = 17;
static constexpr const int KEY_O = 18;
static constexpr const int KEY_P = 19;

static constexpr const int KEY_A = 20;
static constexpr const int KEY_S = 21;
static constexpr const int KEY_D = 22;
static constexpr const int KEY_F = 23;
static constexpr const int KEY_G = 24;
static constexpr const int KEY_H = 25;
static constexpr const int KEY_J = 26;
static constexpr const int KEY_K = 27;
static constexpr const int KEY_L = 28;

static constexpr const int KEY_Z = 29;
static constexpr const int KEY_X = 30;
static constexpr const int KEY_C = 31;
static constexpr const int KEY_V = 32;
static constexpr const int KEY_B = 33;
static constexpr const int KEY_N = 34;
static constexpr const int KEY_M = 35;

static constexpr const int KEY_SPACE     = 36;
static constexpr const int KEY_LEFT      = 37;
static constexpr const int KEY_RIGHT     = 38;
static constexpr const int KEY_UP        = 39;
static constexpr const int KEY_DOWN      = 40;
static constexpr const int KEY_TAB       = 41;
static constexpr const int KEY_BACKSPACE = 42;

static constexpr const int COUNT_OF_KEYS = 43;

static const QMap<int, int> KeysMapper =
{
    {static_cast<int>(Qt::Key_0),  KEY_0},
    {static_cast<int>(Qt::Key_1),  KEY_1},
    {static_cast<int>(Qt::Key_2),  KEY_2},
    {static_cast<int>(Qt::Key_3),  KEY_3},
    {static_cast<int>(Qt::Key_4),  KEY_4},
    {static_cast<int>(Qt::Key_5),  KEY_5},
    {static_cast<int>(Qt::Key_6),  KEY_6},
    {static_cast<int>(Qt::Key_7),  KEY_7},
    {static_cast<int>(Qt::Key_8),  KEY_8},
    {static_cast<int>(Qt::Key_9),  KEY_9},

    {static_cast<int>(Qt::Key_Q),  KEY_Q},
    {static_cast<int>(Qt::Key_W),  KEY_W},
    {static_cast<int>(Qt::Key_E),  KEY_E},
    {static_cast<int>(Qt::Key_R),  KEY_R},
    {static_cast<int>(Qt::Key_T),  KEY_T},
    {static_cast<int>(Qt::Key_Y),  KEY_Y},
    {static_cast<int>(Qt::Key_U),  KEY_U},
    {static_cast<int>(Qt::Key_I),  KEY_I},
    {static_cast<int>(Qt::Key_O),  KEY_O},
    {static_cast<int>(Qt::Key_P),  KEY_P},

    {static_cast<int>(Qt::Key_A),  KEY_A},
    {static_cast<int>(Qt::Key_S),  KEY_S},
    {static_cast<int>(Qt::Key_D),  KEY_D},
    {static_cast<int>(Qt::Key_F),  KEY_F},
    {static_cast<int>(Qt::Key_G),  KEY_G},
    {static_cast<int>(Qt::Key_H),  KEY_H},
    {static_cast<int>(Qt::Key_J),  KEY_J},
    {static_cast<int>(Qt::Key_K),  KEY_K},
    {static_cast<int>(Qt::Key_L),  KEY_L},

    {static_cast<int>(Qt::Key_Z),  KEY_Z},
    {static_cast<int>(Qt::Key_X),  KEY_X},
    {static_cast<int>(Qt::Key_C),  KEY_C},
    {static_cast<int>(Qt::Key_V),  KEY_V},
    {static_cast<int>(Qt::Key_B),  KEY_B},
    {static_cast<int>(Qt::Key_N),  KEY_N},
    {static_cast<int>(Qt::Key_M),  KEY_N},

    {static_cast<int>(Qt::Key_Space),  KEY_SPACE},
    {static_cast<int>(Qt::Key_Left),   KEY_LEFT},
    {static_cast<int>(Qt::Key_Right),  KEY_RIGHT},
    {static_cast<int>(Qt::Key_Up),     KEY_UP},
    {static_cast<int>(Qt::Key_Down),   KEY_DOWN},
    {static_cast<int>(Qt::Key_Tab),    KEY_TAB},

    {static_cast<int>(Qt::Key_Backspace),    KEY_BACKSPACE}
};
}

namespace SCREEN
{
    static constexpr const QSize LOGICAL_SIZE  = QSize(640, 480);
    static constexpr const QSize CELL_SIZE     = QSize(1  , 1  );
    static constexpr const QSize PHYSICAL_SIZE = QSize(LOGICAL_SIZE.width()  * CELL_SIZE.width(),
                                                       LOGICAL_SIZE.height() * CELL_SIZE.height());
}

namespace LAYER
{
    static constexpr const int BG = -10;
    static constexpr const int ENTITY = 10;
}

static const float RAD_TO_DEGREE  = 180.0f/3.14f;
static const float DEGREE_TO_RAD  = 3.14f/180.0f;

#endif // UTILS_H

