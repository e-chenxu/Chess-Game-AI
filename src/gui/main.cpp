#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QVector>
#include <iostream>


class ChessBoard : public QWidget {
public:
    ChessBoard(QWidget *parent = nullptr) : QWidget(parent) {
        qDebug() << "Initializing ChessBoard...";

        QGridLayout *layout = new QGridLayout(this);
        layout->setSpacing(0);
        setFixedSize(400, 400);
        
        qDebug() << "Chessboard layout set.";

        QVector<QVector<QString>> initialBoard = {
            {"bR", "bN", "bB", "bQ", "bK", "bB", "bN", "bR"},
            {"bP", "bP", "bP", "bP", "bP", "bP", "bP", "bP"},
            {"", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", ""},
            {"", "", "", "", "", "", "", ""},
            {"wP", "wP", "wP", "wP", "wP", "wP", "wP", "wP"},
            {"wR", "wN", "wB", "wQ", "wK", "wB", "wN", "wR"}
        };

        qDebug() << "Board initialized, now creating UI...";

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                QLabel *square = new QLabel(this);
                square->setFixedSize(50, 50);
                square->setAlignment(Qt::AlignCenter);

                if ((row + col) % 2 == 0)
                    square->setStyleSheet("background-color: #eeeed2;");
                else
                    square->setStyleSheet("background-color: #769656;");

                if (!initialBoard[row][col].isEmpty()) {
                    QString imgPath = "../resources/pieces/" + initialBoard[row][col] + ".png";
                    QPixmap piecePixmap(imgPath);

                    if (piecePixmap.isNull()) {
                        qDebug() << "Failed to load image:" << imgPath;
                    } else {
                        square->setPixmap(piecePixmap.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    }
                }

                layout->addWidget(square, row, col);
            }
        }

        setLayout(layout);
        qDebug() << "Chessboard UI created successfully!";
    }

};

int main(int argc, char *argv[]) {
    std::cout << "Before QApplication" << std::endl;
    QApplication app(argc, argv);
    std::cout << "Starting Chess GUI..." << std::endl;
    
    ChessBoard board;
    board.show();

    return app.exec();
}