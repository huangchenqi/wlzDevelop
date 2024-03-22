#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineF>
#include <QPointF>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLegendMarker>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtCore/QtMath>
const float Pi = 3.14159f;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_chart(new QChart()),
    m_series1(new QLineSeries()),
    m_series2(new QLineSeries()),
    m_series3(new QLineSeries()),
    scatterSeries(new QScatterSeries()),
    twoScatterSeries(new QScatterSeries()),
    threeScatterSeries(new QScatterSeries()),
    markScatterSeries(new QScatterSeries())
{
    ui->setupUi(this);
    // 设置图表标题
    m_chart->setTitle("Temperature Data");

    // 创建温度曲线图1并设置属性
    m_series1->setName(tr("Device 1"));
    m_series1->setColor(Qt::red);
    m_series1->setPen(QPen(Qt::red, 2));
    m_chart->addSeries(m_series1);
    m_chart->addSeries(scatterSeries);

    // 设置散点标记的颜色
    scatterSeries->setColor(QColor(Qt::red));
    scatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    scatterSeries->setMarkerSize(10);
    scatterSeries->setVisible(true);
    scatterSeries->setOpacity(0.01);
    markScatterSeries->setColor(QColor(Qt::yellow));
    markScatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    markScatterSeries->setMarkerSize(20);
    markScatterSeries->setVisible(false);
    m_chart->addSeries(markScatterSeries);
    twoScatterSeries->setColor(QColor(Qt::green));
    twoScatterSeries->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    twoScatterSeries->setMarkerSize(10);
    twoScatterSeries->setVisible(false);
    threeScatterSeries->setColor(QColor(Qt::blue));
    threeScatterSeries->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    threeScatterSeries->setMarkerSize(30);
    threeScatterSeries->setVisible(false);

    // 添加散点系列到图表中

    m_chart->addSeries(twoScatterSeries);
    m_chart->addSeries(threeScatterSeries);

    //m_chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);


    // 创建温度曲线图2并设置属性
    m_series2->setName(tr("Device 2"));
    m_series2->setColor(Qt::green);
    m_series2->setPen(QPen(Qt::green, 2));
    m_chart->addSeries(m_series2);

    // 创建温度曲线图3并设置属性
    m_series3->setName(tr("Device 3"));
    m_series3->setColor(Qt::blue);
    m_series3->setPen(QPen(Qt::blue, 2));
    m_chart->addSeries(m_series3);

    // 设置横轴属性
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 1000);
    axisX->setTitleText("Time (s)");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series1->attachAxis(axisX);
    m_series2->attachAxis(axisX);
    m_series3->attachAxis(axisX);
    scatterSeries->attachAxis(axisX);
    //axisX->setLabelFormat("%.2f");
    twoScatterSeries->attachAxis(axisX);
    threeScatterSeries->attachAxis(axisX);
    markScatterSeries->attachAxis(axisX);
    // 设置纵轴属性
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 30000);
    axisY->setTitleText("Temperature (℃)");
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series1->attachAxis(axisY);
    m_series2->attachAxis(axisY);
    m_series3->attachAxis(axisY);
    scatterSeries->attachAxis(axisY);
    twoScatterSeries->attachAxis(axisY);
    threeScatterSeries->attachAxis(axisY);
    markScatterSeries->attachAxis(axisY);

    updateChartData();
    // 将图表添加到ChartView中
    QPainterPath starPath;
    starPath.moveTo(28, 15);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(14 + 14 * qCos(0.8 * i * Pi),
                        15 + 14 * qSin(0.8 * i * Pi));
    }
    starPath.closeSubpath();
    QImage star(30, 30, QImage::Format_ARGB32);
    star.fill(Qt::transparent);

    QPainter painter(&star);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QRgb(0xf6a625));
    painter.setBrush(painter.pen().color());
    painter.drawPath(starPath);



    threeScatterSeries->setBrush(star);
    threeScatterSeries->setPen(QColor(Qt::transparent));
    ui->chartView->setChart(m_chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    //ui->chartView->setRubberBand(QChartView::setHorizontalRubberBand);

    connect(scatterSeries, &QScatterSeries::clicked, this, &MainWindow::onOneScatterSeriesClicked);
    connect(m_series2, &QLineSeries::clicked, this, &MainWindow::onTwoChartClicked);
    connect(m_series3, &QLineSeries::clicked, this, &MainWindow::onThreeChartClicked);
    //connect(scatterSeries,&QScatterSeries::clicked,this,&MainWindow::onCancelClicked);
    connect(ui->oneCheckBox,&QCheckBox::stateChanged,this,&MainWindow::onOneCheckBoxClicked);
    connect(ui->twoCheckBox,&QCheckBox::stateChanged,this,&MainWindow::onTwoCheckBoxClicked);
    connect(ui->threeCheckBox,&QCheckBox::stateChanged,this,&MainWindow::onThreeCheckBoxClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}
 void MainWindow::updateChartData()
 {


     // 在温度曲线上增加一个点，模拟温度数据变化
     for(int i=0;i<1000;i++){
         QPointF p1(i, qrand());
         QPointF p2(i, qrand() % 10 + 30);
         QPointF p3(i, qrand() % 10 + 40);
         m_series1->append(p1);
         m_series2->append(p2);
         m_series3->append(p3);
         scatterSeries->append(p1);
     }



 }

// void MainWindow::mousePress(QMouseEvent *event) {
//         // 获取鼠标点击的点的位置
//         QPointF clickedPoint = ui->chartView->chart()->mapToValue(event->pos());

//         // 创建QScatterSeries并设置标记点
//         QScatterSeries *scatterSeries = new QScatterSeries();
//         scatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
//         scatterSeries->setMarkerSize(10);
//         scatterSeries->append(clickedPoint);

//         // 添加散点系列到图表中
//         m_chart->addSeries(scatterSeries);

//         // 设置散点标记的颜色
//         scatterSeries->setColor(QColor(Qt::red));
//     }
 void MainWindow::onOneScatterSeriesClicked(const QPointF &point){
     //     QPointF chartPoint = m_chart->mapToValue(point);
              qDebug()<<"localPoint"<<point;
             // 转换点击位置到图表坐标
              //QPointF scenePoint = ui->chartView->mapToScene(point.toPoint());
              // 将场景坐标系中的点映射到图表坐标系中
              QPointF chartPoint = point;//m_chart->mapFromScene(scenePoint);
              qDebug()<<"sum"<<markScatterSeries->count();
              //scatterSeries->append(chartPoint);

              qDebug() << "sum" << markScatterSeries->count();

              if(markScatterSeries->count() > 0){
                  bool found = false;
                      // 检查散点是否已存在，如果存在，则删除；如果不存在，则添加
                      for (int i = 0; i < markScatterSeries->count(); i++) {
                          if (markScatterSeries->at(i) == point) {
                              markScatterSeries->remove(i);
                              qDebug() << "delete";
                              found = true;
                              break;
                          }
                      }
                      if (!found) {
                          markScatterSeries->append(chartPoint);
                          qDebug() << "append";
                      }
              }else{
                  markScatterSeries->append(chartPoint);
                  qDebug()<<"countPoint"<<chartPoint<<markScatterSeries->count();
              }

              ui->chartView->setChart(m_chart);

              qDebug()<<chartPoint;
              int i = 1;
              ++i;

              // 输出点击次数到控制台
              qDebug() << "Total clicks: " <<i;
              QFont font("Arial", 10);
              markScatterSeries->setVisible(true);
              markScatterSeries->setPointLabelsColor(Qt::red);

              markScatterSeries->setPointLabelsFont(font);
              markScatterSeries->setPointLabelsVisible(true);
              markScatterSeries->setPointLabelsClipping(false);
              QString scatterPoint = "Time: @xPoint\tTemp: @yPoint";
              qDebug()<<"ttttscatterPoint"<<scatterPoint.toUtf8();
              markScatterSeries->setPointLabelsFormat("Time: @xPoint\\nTemp: @yPoint");
 }
 void MainWindow::onTwoScatterSeriesClicked(const QPointF &point){

 }
 void MainWindow::onThreeScatterSeriesClicked(const QPointF &point){

 }
 void MainWindow::onChartClicked(const QPointF &point) {

//     QPointF chartPoint = m_chart->mapToValue(point);
         qDebug()<<"localPoint"<<point;
        // 转换点击位置到图表坐标
         //QPointF scenePoint = ui->chartView->mapToScene(point.toPoint());
         // 将场景坐标系中的点映射到图表坐标系中
         QPointF chartPoint = point;//m_chart->mapFromScene(scenePoint);
         qDebug()<<"sum"<<scatterSeries->count();
         //scatterSeries->append(chartPoint);

         qDebug() << "sum" << scatterSeries->count();
         if(scatterSeries->count() == 0){
             scatterSeries->append(chartPoint);
             qDebug()<<"countPoint"<<chartPoint;
         }else{
             for (int i = 0; i < scatterSeries->count(); ++i) {
                 if(scatterSeries->at(i) == chartPoint){
                         scatterSeries->remove(scatterSeries->at(i));
                         qDebug()<<"delete";
                         break;
                     }else{
                         scatterSeries->append(chartPoint);
                         qDebug()<<"append";
                         break;
                   }

             }
         }

         qDebug()<<chartPoint;
         int i = 1;
         ++i;

         // 输出点击次数到控制台
         qDebug() << "Total clicks: " <<i;
         QFont font("Arial", 10);

         scatterSeries->setPointLabelsColor(Qt::red);

         scatterSeries->setPointLabelsFont(font);
         scatterSeries->setPointLabelsVisible(true);
         scatterSeries->setPointLabelsClipping(false);
         QString scatterPoint = "Time: @xPoint\tTemp: @yPoint";
         qDebug()<<"ttttscatterPoint"<<scatterPoint.toUtf8();
         scatterSeries->setPointLabelsFormat("Time: @xPoint\\nTemp: @yPoint");

#if 0         // 获取散点系列中所有的点
            QList<QPointF> points = scatterSeries->points();
         // 显示所有点的坐标

            for (const QPointF &p : points) {
//                QGraphicsTextItem *textItem = new QGraphicsTextItem(m_chart);
//                textItem->setPlainText(QString("lo:%1\nX: %2\nY: %3").arg(i).arg(p.x()).arg(p.y()));
//                textItem->setPos(p);
//                m_chart->scene()->addItem(textItem);

//                i++;
            }

#endif


            // 添加所有的点并设置标签
//            foreach (const QPointF &scatterPoint, scatterSeries->points()) {
//                QString label = QString("X: %1\nY: %2").arg(scatterPoint.x()).arg(scatterPoint.y());
//                scatterSeries->setPointLabelsVisible(true);
//                scatterSeries->setPointLabelsFormat(label);
//                scatterSeries->setPointLabelsColor(Qt::red);
//                QFont font("Arial", 10);
//                scatterSeries->setPointLabelsFont(font);
//            }





 }

 void MainWindow::onTwoChartClicked(const QPointF &point) {

//     QPointF chartPoint = m_chart->mapToValue(point);
         qDebug()<<"localPoint"<<point;
        // 转换点击位置到图表坐标
         //QPointF scenePoint = ui->chartView->mapToScene(point.toPoint());
         // 将场景坐标系中的点映射到图表坐标系中
         QPointF chartPoint = point;//m_chart->mapFromScene(scenePoint);
         qDebug()<<"sum"<<twoScatterSeries->count();
         //scatterSeries->append(chartPoint);

         qDebug() << "sum" << twoScatterSeries->count();
         if(twoScatterSeries->count() == 0){
             twoScatterSeries->append(chartPoint);
             qDebug()<<"countPoint"<<chartPoint;
         }else{
             for (int i = 0; i < twoScatterSeries->count(); ++i) {
                 if(twoScatterSeries->at(i) == chartPoint){
                         twoScatterSeries->remove(twoScatterSeries->at(i));
                         qDebug()<<"delete";
                         break;
                     }else{
                         twoScatterSeries->append(chartPoint);
                         qDebug()<<"append";
                         break;
                   }

             }
         }

         qDebug()<<chartPoint;
         int i = 1;
         ++i;

         // 输出点击次数到控制台
         qDebug() << "Total clicks: " <<i;
         QFont font("Arial", 10);

         twoScatterSeries->setPointLabelsColor(Qt::green);

         twoScatterSeries->setPointLabelsFont(font);
         twoScatterSeries->setPointLabelsVisible(true);
         twoScatterSeries->setPointLabelsClipping(false);
         QString scatterPoint = "Time: @xPoint\nTemp: @yPoint";
         twoScatterSeries->setPointLabelsFormat("Time: @xPoint<br>Temp: @yPoint");


 }
 void MainWindow::onThreeChartClicked(const QPointF &point) {

//     QPointF chartPoint = m_chart->mapToValue(point);
         qDebug()<<"localPoint"<<point;
        // 转换点击位置到图表坐标
         //QPointF scenePoint = ui->chartView->mapToScene(point.toPoint());
         // 将场景坐标系中的点映射到图表坐标系中
         QPointF chartPoint =point;// m_chart->mapFromScene(scenePoint);
         qDebug()<<"sum"<<threeScatterSeries->count();
         //scatterSeries->append(chartPoint);

         qDebug() << "sum" << threeScatterSeries->count();
         if(threeScatterSeries->count() == 0){
             threeScatterSeries->append(chartPoint);
             qDebug()<<"countPoint"<<chartPoint;
         }else{
             for (int i = 0; i < threeScatterSeries->count(); ++i) {
                 if(threeScatterSeries->at(i) == chartPoint){
                         threeScatterSeries->remove(threeScatterSeries->at(i));
                         qDebug()<<"delete";
                         break;
                     }else{
                         threeScatterSeries->append(chartPoint);
                         qDebug()<<"append";
                         break;
                   }

             }
         }

         qDebug()<<chartPoint;
         int i = 1;
         ++i;

         // 输出点击次数到控制台
         qDebug() << "Total clicks: " <<i;
         QFont font("Arial", 10);

         threeScatterSeries->setPointLabelsColor(Qt::blue);

         threeScatterSeries->setPointLabelsFont(font);
         threeScatterSeries->setPointLabelsVisible(true);
         threeScatterSeries->setPointLabelsClipping(false);
         QString scatterPoint = QString("Time: @xPoint-r-nTemp: @yPoint");
         threeScatterSeries->setPointLabelsFormat("Time: @xPoint\nTemp: @yPoint");


 }
 void MainWindow::showCoordinate(const QPointF &point) {
//     QGraphicsTextItem *textItem = new QGraphicsTextItem(m_chart);
//     int i=1;
//     textItem->setPlainText(QString("lo:%1\nX: %2\nY: %3").arg(i).arg(point.x()).arg(point.y()));
//     textItem->setPos(point);

//     m_chart->scene()->addItem(textItem);
//     QGraphicsSimpleTextItem *cursorData;
//     cursorData = new QGraphicsSimpleTextItem(m_chart);
//     QPoint curPos=mapFromGlobal(QCursor::pos());
//     cursorData->setPos(curPos.x(),curPos.y());
//     cursorData->setText(QString("%1,%2").arg(point.x()).arg(point.y()));
     //ui->chartView->scene()->addItem(textItem);
 //    i++;

}
//void MainWindow::mousePressEvent(QMouseEvent *event){
//         QPointF chartPoint = ui->chartView->mapToScene(event->pos()).toPointF();
//         // 根据 chartPoint 获取相应的数据点或进行其他操作
//         QChartView::mousePressEvent(event);
//         qDebug()<<"chartPoint:"<<chartPoint;
//     }

void MainWindow::on_saveButton_clicked()
{
    QPixmap pixmap = ui->chartView->grab();
    pixmap.save("save.png");
    QMessageBox::information(nullptr,QStringLiteral("保存提示"),QStringLiteral("保存成功"));
}
void MainWindow::onOneCheckBoxClicked(int state)
{

        if(state == Qt::Checked){
            m_series1->setVisible(true);
            scatterSeries->setVisible(true); // 设置散点可见
            scatterSeries->setOpacity(1.0);  // 设置散点不透明
            scatterSeries->setPointLabelsVisible(true); // 启用散点

        }else if(state == Qt::Unchecked){
            m_series1->setVisible(false);
            scatterSeries->setVisible(false); // 设置散点不可见
            scatterSeries->setOpacity(0.0);   // 设置散点透明
            scatterSeries->setPointLabelsVisible(false); // 启用散点

        }else{
            qDebug()<<"选择错误";
        }

}
void MainWindow::onTwoCheckBoxClicked(int state){
    if(state == Qt::Checked){
        m_series2->setVisible(true);
        twoScatterSeries->setVisible(true); // 设置散点可见
        twoScatterSeries->setOpacity(1.0);  // 设置散点不透明
        twoScatterSeries->setPointLabelsVisible(true); // 启用散点
    }else if(state == Qt::Unchecked){
        m_series2->setVisible(false);
        twoScatterSeries->setVisible(false); // 设置散点不可见
        twoScatterSeries->setOpacity(0.0);   // 设置散点透明
        twoScatterSeries->setPointLabelsVisible(false); // 启用散点

    }else{
        qDebug()<<"选择错误";
    }
}
void MainWindow::onThreeCheckBoxClicked(int state){
    if(state == Qt::Checked){
        m_series3->setVisible(true);
        threeScatterSeries->setVisible(true); // 设置散点可见
        threeScatterSeries->setOpacity(1.0);  // 设置散点不透明
        threeScatterSeries->setPointLabelsVisible(true); // 启用散点
    }else if(state == Qt::Unchecked){
        m_series3->setVisible(false);
        threeScatterSeries->setVisible(false); // 设置散点不可见
        threeScatterSeries->setOpacity(0.0);   // 设置散点透明
        threeScatterSeries->setPointLabelsVisible(false); // 启用散点
    }else{
        qDebug()<<"选择错误";
    }
}
void MainWindow::onCancelClicked(const QPointF &point){
    // 转换点击位置到图表坐标
     QPointF scenePoint = ui->chartView->mapToScene(point.toPoint());
     // 将场景坐标系中的点映射到图表坐标系中
     QPointF chartPoint = m_chart->mapFromScene(scenePoint);


    for (int i = 0; i < scatterSeries->count(); ++i) {
        if (chartPoint == scatterSeries->at(i)) {
            scatterSeries->remove(scatterSeries->at(i));
            qDebug() << "deleteScatter" << chartPoint;
            break;
        }
    }

}
void MainWindow::mouseMoveEvent(QMouseEvent *pEvent)
{
     if (m_bMiddleButtonPressed)
     {
         QPoint oDeltaPos = pEvent->pos() - m_oPrePos;
         m_chart->scroll(-oDeltaPos.x(), oDeltaPos.y());
         m_oPrePos = pEvent->pos();
     }
     __super::mouseMoveEvent(pEvent);
}
void MainWindow::mousePressEvent(QMouseEvent *pEvent)
{
     if (pEvent->button() == Qt::MiddleButton)
     {
         m_bMiddleButtonPressed = true;
         m_oPrePos = pEvent->pos();
         this->setCursor(Qt::OpenHandCursor);
     }
     __super::mousePressEvent(pEvent);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *pEvent)
{
     if (pEvent->button() == Qt::MiddleButton)
     {
         m_bMiddleButtonPressed = false;
         this->setCursor(Qt::ArrowCursor);
     }
     __super::mouseReleaseEvent(pEvent);
}
void MainWindow::wheelEvent(QWheelEvent *pEvent)
{
     qreal rVal = std::pow(0.999, pEvent->delta()); // 设置比例
     // 1. 读取视图基本信息
     QRectF oPlotAreaRect = m_chart->plotArea();
     QPointF oCenterPoint = oPlotAreaRect.center();
     // 2. 水平调整
     oPlotAreaRect.setWidth(oPlotAreaRect.width() * rVal);
     // 3. 竖直调整
     oPlotAreaRect.setHeight(oPlotAreaRect.height() * rVal);
     // 4.1 计算视点，视点不变，围绕中心缩放
     //QPointF oNewCenterPoint(oCenterPoint);
     // 4.2 计算视点，让鼠标点击的位置移动到窗口中心
     //QPointF oNewCenterPoint(pEvent->pos());
     // 4.3 计算视点，让鼠标点击的位置尽量保持不动(等比换算，存在一点误差)
     QPointF oNewCenterPoint(2 * oCenterPoint - pEvent->pos() - (oCenterPoint - pEvent->pos()) / rVal);
     // 5. 设置视点
     oPlotAreaRect.moveCenter(oNewCenterPoint);
     // 6. 提交缩放调整
     m_chart->zoomIn(oPlotAreaRect);
     __super::wheelEvent(pEvent);
}
