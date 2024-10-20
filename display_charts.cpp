// display_charts.cpp
#include "display_charts.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <map>
#include <set>

QT_CHARTS_USE_NAMESPACE

void display_charts(const std::vector<PerformanceResult>& results) {
    std::map<std::string, std::map<std::string, std::map<int, double>>> data_map;
    std::set<int> sizes_set;

    for (const auto& result : results) {
        data_map[result.generator_name][result.sorter_name][result.data_size] = result.average_time;
        sizes_set.insert(result.data_size);
    }

    std::vector<int> sizes(sizes_set.begin(), sizes_set.end());
    std::sort(sizes.begin(), sizes.end());

    QMainWindow window;
    QWidget *centralWidget = new QWidget(&window);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    for (const auto& generator_pair : data_map) {
        const std::string& generator_name = generator_pair.first;
        const auto& sorters_map = generator_pair.second;

        QChart *chart = new QChart();
        chart->setTitle(QString::fromStdString("Performance for " + generator_name + " Data"));
        chart->setAnimationOptions(QChart::AllAnimations);

        QLineSeries *series;
        std::map<std::string, QLineSeries*> sorter_series_map;

        for (const auto& sorter_pair : sorters_map) {
            const std::string& sorter_name = sorter_pair.first;
            series = new QLineSeries();
            series->setName(QString::fromStdString(sorter_name));

            const auto& size_time_map = sorter_pair.second;

            for (int size : sizes) {
                auto it = size_time_map.find(size);
                if (it != size_time_map.end()) {
                    series->append(size, it->second);
                }
            }

            chart->addSeries(series);
        }

        chart->createDefaultAxes();
        chart->axes(Qt::Horizontal).first()->setTitleText("Data Size");
        chart->axes(Qt::Vertical).first()->setTitleText("Average Time (seconds)");

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        layout->addWidget(chartView);
    }

    window.setCentralWidget(centralWidget);
    window.resize(800, 600);
    window.show();

    QApplication::exec();
}
