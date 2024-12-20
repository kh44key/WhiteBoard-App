#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QStack>

class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
    explicit WhiteBoard(QWidget* parent = 0);
    void setPenColor(const QColor& newColor);
    void setPenSize(int newSize);

public slots:
    void clearImage();
    void undo(); // New slot for undo
    void redo(); // New slot for redo

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;


private:
    void drawLineTo(const QPoint& endPoint);
    void resizeImage(QImage* image, const QSize& newSize);

    bool m_drawing;
    bool m_modified;
    int m_penWidth;
    QColor m_penColor;
    QImage m_image;
    QPoint m_lastPoint;

    QStack<QImage> m_undoStack; // Stack to store undo states
    QStack<QImage> m_redoStack; // Stack to store redo states

};

#endif // WHITEBOARD_H
