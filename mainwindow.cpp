#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
bool MainWindow::isPlaning = true;

//js����c++�ӿ�
jsValue JS_CALL jsInvokeC(jsExecState es)
{
    QMessageBox::about(NULL,QString::fromLocal8Bit("��ʾ"),jsToString(es, jsArg(es, 0)));
    return jsUndefined();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    //����wke������� wkedefine.h
    //����wkeWebViewʵ��������󶨵�qt�����е�widget�ؼ�
    qDebug() << ui->widget->width() << " h" << ui->widget->height();
    webView= wkeCreateWebWindow(WKE_WINDOW_TYPE_CONTROL, (HWND)ui->widget->winId(), 0, 0, 800,600);
    //��ʾwkeWebView
    wkeShowWindow(webView, true);

    wkeSetDebugConfig(webView,"showDevTools","G:/qt_wke/front_end/inspector.html");
    connect(ui->loadUrl,SIGNAL(clicked()),this,SLOT(onLoadurlClicked()));
    connect(ui->openHtml,SIGNAL(clicked()),this,SLOT(onOpenhtmlClicked()));
    //connect(ui->invokeJs,SIGNAL(clicked()),this,SLOT(onInvokejsClicked()));
    //��jsҪ���õ�c++��������һ��������js��ִ�еķ������ڶ���������c++�ж����ȫ�ַ����������������Ƿ������ݵĲ�������
    jsBindFunction("invokeC",jsInvokeC,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* size){
    Q_UNUSED(size)
    //�ı�wkeWebView��ʾ��С
   // wkeResize(webView, ui->widget->width(),ui->widget->height());
}

//������ַ
void MainWindow::onLoadurlClicked()
{
    wkeLoadURL(webView,ui->url->text().toLatin1().data());
}

//���ر���html�ļ�������ȡ����html�е��ı����ݲ�����
void MainWindow::onOpenhtmlClicked()
{
    QFile file("debug/login.html");
    file.open(QIODevice::ReadOnly);
    wkeLoadHTML(webView,file.read(file.bytesAvailable()));
    file.close();
}

//c++����js����
void MainWindow::onInvokejsClicked()
{
    static int count = 0;
    wkeRunJS(webView,QString("cInvokeJs(%1)").arg(++count).toLatin1().data());
}

void MainWindow::on_loadUrl_clicked()
{
    wkeLoadURL(webView,ui->url->text().toLatin1().data());
}

void MainWindow::on_invokeJs_clicked()
{


}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "hello";
    wkeLoadFile(webView,"fs.js");
//    jsExecState  s = wkeGlobalExec(webView);
//    jsValue func = jsString(s,"download");

//    jsValue args[1] = {jsString(s,"hello")};
//    jsCall(s,func,jsUndefined(),args,1);
}
