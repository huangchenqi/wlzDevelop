#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts>
#include <QtCharts/QLineSeries>
#include <QChartView>
#include <QtWidgets>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QChartView *chartView;

    void showCoordinate(const QPointF &point);

private:
    Ui::MainWindow *ui;
private slots:
    void updateChartData(); // 更新数据槽函数


    void onChartClicked(const QPointF &point);
    void onTwoChartClicked(const QPointF &point);
    void onThreeChartClicked(const QPointF &point);
    void onOneScatterSeriesClicked(const QPointF &point);
    void onTwoScatterSeriesClicked(const QPointF &point);
    void onThreeScatterSeriesClicked(const QPointF &point);
    void on_saveButton_clicked();

    void onOneCheckBoxClicked(int state);

    void onTwoCheckBoxClicked(int state);

    void onThreeCheckBoxClicked(int state);
    void onCancelClicked(const QPointF &point);


private:

    QChart *m_chart; // 图表指针

    QLineSeries *m_series1; // 设备1温度曲线
    QLineSeries *m_series2; // 设备2温度曲线
    QLineSeries *m_series3; // 设备3温度曲线
    QScatterSeries *scatterSeries;
    QScatterSeries *markScatterSeries;
    QScatterSeries *twoScatterSeries;
    QScatterSeries *threeScatterSeries;
protected:
    virtual void mouseMoveEvent(QMouseEvent *pEvent)override;
    virtual void mousePressEvent(QMouseEvent *pEvent)override;
    virtual void mouseReleaseEvent(QMouseEvent *pEvent) override;
    virtual void wheelEvent(QWheelEvent *pEvent)override;
private:
    bool m_bMiddleButtonPressed;
    QPoint m_oPrePos;

};

#endif // MAINWINDOW_H
