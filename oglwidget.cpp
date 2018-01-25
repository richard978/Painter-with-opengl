#include "oglwidget.h"
#include "paintfunc.h"
#include <math.h>
#include <QDebug>
void OGLWidget::_init()
{
    dotx = 100;
    doty = 100;
    lineX1=lineX2=lineX3 = 100;
    lineY1=lineY2=lineY3 = 100;
    RectX1=RectX2=RectX3 = 100;
    RectY1=RectY2=RectY3 = 100;
    RRectX1=RRectX2=RRectX3 = 100;
    RRectY1=RRectY2=RRectY3 = 100;
    CirX1=CirX2=CirX3 = 100;
    CirY1=CirY2=CirY3 = 100;
}
OGLWidget::OGLWidget(QWidget *parent):QOpenGLWidget(parent)
{
    activeDot = 0;
    activeLine = 0;
    activeCurve = 0;
    activeRect = 0;
    activeCircle = 0;
    activeRoundRect = 0;
    isRubber = 0;
    
    dotx = 100;
    doty = 100;
    lineX1=lineX2=lineX3 = 100;
    lineY1=lineY2=lineY3 = 100;
    RectX1=RectX2=RectX3 = 100;
    RectY1=RectY2=RectY3 = 100;
    RRectX1=RRectX2=RRectX3 = 100;
    RRectY1=RRectY2=RRectY3 = 100;
    CirX1=CirX2=CirX3 = 100;
    CirY1=CirY2=CirY3 = 100;
    lineReleased = 0;
    rectReleased = 0;
    cirReleased = 0;
    roundRectReleased = 0;
    filled = 0;

    curColor.R = 0;
    curColor.G = 0;
    curColor.B = 0;

    lineWidth = 1.0f;
}

OGLWidget::~OGLWidget()
{

}

void OGLWidget::fileIn(QTextStream &in)
{
    QString line;
    QStringList strList;
    QStringList dataList;
    while(!in.atEnd()){
        line = in.readLine();
        strList << line;
    }
    if(strList.empty())
        return;
    int dotNum=0;
    int lineNum=0;
    int rectNum=0;
    int filledRectNum=0;
    int RRectNum=0;
    int filledRRectNum=0;
    int curvesNum=0;
    int circleNum=0;
    int filledCircleNum=0;
    for(int i=0; i<strList.size();){
        ///qDebug() << strList[i];
        if(strList[i] == "Dot:") {
            dotNum = strList[++i].toInt();
            ++i;
        }
        else if(strList[i] == "Line:"){
            lineNum = strList[++i].toInt();
            ++i;
        }
        else if(strList[i] == "Rectangle:"){
            rectNum = strList[++i].toInt();
            ++i;
        }
        else if(strList[i] == "FilledRectangle:"){
            filledRectNum = strList[++i].toInt();
            ++i;
        }
        else if (strList[i] =="RoundRectangle:"){
            RRectNum = strList[++i].toInt();
            ++i;
        }
        else if (strList[i] =="FilledRoundRectangle:"){
            filledRRectNum = strList[++i].toInt();
            ++i;
        }
        else if (strList[i] =="Curves:"){
            curvesNum = strList[++i].toInt();
            ++i;
        }
        else if (strList[i] =="Circle:"){
            circleNum = strList[++i].toInt();
            ++i;
        }
        else if (strList[i] =="FilledCircle:"){
            filledCircleNum = strList[++i].toInt();
            ++i;
        }
        else{
            dataList.push_back(strList[i]);
            ++i;
        }
    }
    QString temp;
    QStringList templist;
    for(int i=0; i<dataList.size(); ){
        while (dotNum--) {
            dots tempD;
            temp = dataList[i];
            templist = temp.split('|');
            tempD.c.R = templist[0].toFloat();
            tempD.c.G = templist[1].toFloat();
            tempD.c.B = templist[2].toFloat();
            tempD.dotx = templist[3].toFloat();
            tempD.doty = templist[4].toFloat();
            Dlist.push_back(tempD);
            i++;
        }
        while (lineNum--) {
            lines tempL;
            temp = dataList[i];
            templist = temp.split('|');
            tempL.c.R = templist[0].toFloat();
            tempL.c.G = templist[1].toFloat();
            tempL.c.B = templist[2].toFloat();
            tempL.x1 = templist[3].toFloat();
            tempL.x2 = templist[4].toFloat();
            tempL.y1 = templist[5].toFloat();
            tempL.y2 = templist[6].toFloat();
            tempL.w = templist[7].toFloat();
            tempL.released = 1;
            Llist.push_back(tempL);
            i++;
        }
        while (rectNum--) {
            Rects tempRect;
            temp = dataList[i];
            templist = temp.split('|');
            tempRect.c.R = templist[0].toFloat();
            tempRect.c.G = templist[1].toFloat();
            tempRect.c.B = templist[2].toFloat();
            tempRect.x1 = templist[3].toFloat();
            tempRect.x2 = templist[4].toFloat();
            tempRect.y1 = templist[5].toFloat();
            tempRect.y2 = templist[6].toFloat();
            tempRect.w = templist[7].toFloat();
            tempRect.filled = 0;
            tempRect.released = 1;
            Rlist.push_back(tempRect);
            i++;
        }
        while (filledRectNum--) {
            Rects tempfilledRect;
            temp = dataList[i];
            templist = temp.split('|');
            tempfilledRect.c.R = templist[0].toFloat();
            tempfilledRect.c.G = templist[1].toFloat();
            tempfilledRect.c.B = templist[2].toFloat();
            tempfilledRect.x1 = templist[3].toFloat();
            tempfilledRect.x2 = templist[4].toFloat();
            tempfilledRect.y1 = templist[5].toFloat();
            tempfilledRect.y2 = templist[6].toFloat();
            tempfilledRect.w = templist[7].toFloat();
            tempfilledRect.filled = 1;
            tempfilledRect.released = 1;
            Rlist.push_back(tempfilledRect);
            i++;
        }
        while (RRectNum--) {
            RoundRect tempRR;
            temp = dataList[i];
            templist = temp.split('|');
            tempRR.c.R = templist[0].toFloat();
            tempRR.c.G = templist[1].toFloat();
            tempRR.c.B = templist[2].toFloat();
            tempRR.x = templist[3].toFloat();
            tempRR.y = templist[4].toFloat();
            tempRR.h = templist[5].toFloat();
            tempRR.w = templist[6].toFloat();
            tempRR.wid = templist[7].toFloat();
            tempRR.filled = 0;
            tempRR.released = 1;
            RRlist.push_back(tempRR);
            i++;
        }
        while (filledRRectNum--) {
            RoundRect filledtempRR;
            temp = dataList[i];
            templist = temp.split('|');
            filledtempRR.c.R = templist[0].toFloat();
            filledtempRR.c.G = templist[1].toFloat();
            filledtempRR.c.B = templist[2].toFloat();
            filledtempRR.x = templist[3].toFloat();
            filledtempRR.y = templist[4].toFloat();
            filledtempRR.h = templist[5].toFloat();
            filledtempRR.w = templist[6].toFloat();
            filledtempRR.wid = templist[7].toFloat();
            filledtempRR.filled = 1;
            filledtempRR.released =1;
            RRlist.push_back(filledtempRR);
            i++;
        }
        while (curvesNum--) {
            curves cur;
            temp = dataList[i];
            templist = temp.split('|');
            cur.c.R = templist[0].toFloat();
            cur.c.G = templist[1].toFloat();
            cur.c.B = templist[2].toFloat();
            cur.x1 = templist[3].toFloat();
            cur.x2 = templist[4].toFloat();
            cur.x3 = templist[5].toFloat();
            cur.x4 = templist[6].toFloat();
            cur.y1 = templist[7].toFloat();
            cur.y2 = templist[8].toFloat();
            cur.y3 = templist[9].toFloat();
            cur.y4 = templist[10].toFloat();
            cur.w = templist[11].toFloat();
            Curlist.push_back(cur);
            i++;
        }
        while (circleNum--) {
            Circles tempcir;
            temp = dataList[i];
            templist = temp.split('|');
            tempcir.c.R = templist[0].toFloat();
            tempcir.c.G = templist[1].toFloat();
            tempcir.c.B = templist[2].toFloat();
            tempcir.x1 = templist[3].toFloat();
            tempcir.x2 = templist[4].toFloat();
            tempcir.y1 = templist[5].toFloat();
            tempcir.y2 = templist[6].toFloat();
            tempcir.w = templist[7].toFloat();
            tempcir.filled = 0;
            tempcir.released =1;
            Clist.push_back(tempcir);
            i++;
        }
        while (filledCircleNum--) {
            Circles filledtempRR;
            temp = dataList[i];
            templist = temp.split('|');
            filledtempRR.c.R = templist[0].toFloat();
            filledtempRR.c.G = templist[1].toFloat();
            filledtempRR.c.B = templist[2].toFloat();
            filledtempRR.x1 = templist[3].toFloat();
            filledtempRR.x2 = templist[4].toFloat();
            filledtempRR.y1 = templist[5].toFloat();
            filledtempRR.y2 = templist[6].toFloat();
            filledtempRR.w = templist[7].toFloat();
            filledtempRR.filled = 1;
            filledtempRR.released = 1;
            Clist.push_back(filledtempRR);
            i++;
        }

    }
    update();
}

void OGLWidget::dotsOut(QTextStream &out)
{
    if(Dlist.empty())
        return;
    out << "Dot:" <<"\n";
    out << Dlist.size() << "\n";
    for(int i=0; i<Dlist.size(); ++i)
        out << Dlist[i].c.R << "|" << Dlist[i].c.G << "|" << Dlist[i].c.B << "|"
            << Dlist[i].dotx << "|" << Dlist[i].doty << "\n";

}

void OGLWidget::linesOut(QTextStream &out)
{
    if(Llist.empty())
        return;
    out << "Line:" <<"\n";
    out << Llist.size() << "\n";
    for(int i=0; i<Llist.size(); ++i)
        out << Llist[i].c.R << "|" << Llist[i].c.G << "|" << Llist[i].c.B << "|"
            << Llist[i].x1 << "|" << Llist[i].x2 << "|" <<Llist[i].y1 << "|" << Llist[i].y2 << "|" << Llist[i].w << "\n";
}

void OGLWidget::rectsOut(QTextStream &out)
{
    if(Rlist.empty())
        return;
    int count = 0;
    for(int i=0; i<Rlist.size(); ++i){
        if(!Rlist[i].filled)
            count++;
    }
    out << "Rectangle:"  <<"\n";
    out << count << "\n";
    for(int i=0; i<Rlist.size(); ++i){
        if(!Rlist[i].filled)
            out << Rlist[i].c.R << "|" << Rlist[i].c.G << "|" << Rlist[i].c.B << "|"
                << Rlist[i].x1 << "|" << Rlist[i].x2 << "|" << Rlist[i].y1 << "|" << Rlist[i].y2 << "|" << Rlist[i].w <<"\n";
    }
    out << "FilledRectangle:"  <<"\n";
    out << Rlist.size()-count << "\n";
    for(int i=0; i<Rlist.size(); ++i){
        if(Rlist[i].filled)
            out << Rlist[i].c.R << "|" << Rlist[i].c.G << "|" << Rlist[i].c.B << "|"
                << Rlist[i].x1 << "|" << Rlist[i].x2 << "|" << Rlist[i].y1 << "|" << Rlist[i].y2 << "|" << Rlist[i].w <<"\n";
    }
}

void OGLWidget::roundRectsOut(QTextStream &out)
{
    if(RRlist.empty())
        return;
    int count = 0;
    for(int i=0; i<RRlist.size(); ++i){
        if(!RRlist[i].filled)
            count++;
    }

    out << "RoundRectangle:"  <<"\n";
    out << count <<"\n";
    for(int i=0; i<RRlist.size(); ++i){
        if(!RRlist[i].filled)
            out << RRlist[i].c.R << "|" << RRlist[i].c.G << "|" << RRlist[i].c.B << "|"
                << RRlist[i].x << "|" << RRlist[i].y << "|" << RRlist[i].h << "|" << RRlist[i].w << "|" << RRlist[i].wid <<"\n";
    }
    out << "FilledRoundRectangle:"  << "\n";
    out << RRlist.size()-count <<"\n";
    for(int i=0; i<RRlist.size(); ++i){
        if(RRlist[i].filled)
            out << RRlist[i].c.R << "|" << RRlist[i].c.G << "|" << RRlist[i].c.B << "|"
                << RRlist[i].x << "|" << RRlist[i].y << "|" << RRlist[i].h << "|" << RRlist[i].w << "|" << RRlist[i].wid <<"\n";
    }
}

void OGLWidget::curvesOut(QTextStream &out)
{
    if(Curlist.empty())
        return;
    out << "Curves:" <<"\n";
    out << Curlist.size() <<"\n";
    for(int i=0; i<Curlist.size(); ++i)
        out << Curlist[i].c.R << "|" << Curlist[i].c.G << "|" << Curlist[i].c.B << "|"
            << Curlist[i].x1 << "|" << Curlist[i].x2 << "|" << Curlist[i].x3 << "|" << Curlist[i].x4 << "|"
            << Curlist[i].y1 << "|" << Curlist[i].y2 << "|" << Curlist[i].y3 << "|" << Curlist[i].y4 << "|" << Curlist[i].w << "\n";
}

void OGLWidget::circlesOut(QTextStream &out)
{
    if(Clist.empty())
        return;
    int count = 0;
    for(int i=0; i<Clist.size(); ++i){
        if(!Clist[i].filled)
            count++;
    }
    out << "Circle:" <<"\n";
    out  << count <<"\n";
    for(int i=0; i<Clist.size(); ++i){
        if(!Clist[i].filled)
            out << Clist[i].c.R << "|" << Clist[i].c.G << "|" << Clist[i].c.B << "|"
                << Clist[i].x1 << "|" << Clist[i].x2 << "|" << Clist[i].y1 << "|" << Clist[i].y2 << "|" << Clist[i].w <<"\n";
    }
    out << "FilledCircle:" <<"\n";
    out << Clist.size()-count <<"\n";
    for(int i=0; i<Clist.size(); ++i){
        if(Clist[i].filled)
            out << Clist[i].c.R << "|" << Clist[i].c.G << "|" << Clist[i].c.B << "|"
                << Clist[i].x1 << "|" << Clist[i].x2 << "|" << Clist[i].y1 << "|" << Clist[i].y2 << "|" << Clist[i].w <<"\n";
    }
}

void OGLWidget::choosepattern(int id)
{
    switch (id) {
    case 1:
        activeDot = 1;
        activeLine = 0;
        activeCurve = 0;
        activeRect = 0;
        activeCircle = 0;
        activeRoundRect = 0;
        activeDrag = 0;
        break;
    case 2:
        activeDot = 0;
        activeLine = 1;
        activeCurve = 0;
        activeRect = 0;
        activeCircle = 0;
        activeRoundRect = 0;
        activeDrag = 0;
        break;
    case 3:
        activeDot = 0;
        activeLine = 0;
        activeCurve = 0;
        activeRect = 1;
        activeCircle = 0;
        activeRoundRect = 0;
        activeDrag = 0;
        filled = 1;
        break;
    case 4:
        activeDot = 0;
        activeLine = 0;
        activeCurve = 0;
        activeRect = 1;
        activeCircle = 0;
        activeRoundRect = 0;
        filled = 0;
        activeDrag = 0;
        break;
    case 5:
        activeDot = 0;
        activeLine = 0;
        activeCurve = 0;
        activeRect = 0;
        activeCircle = 1;
        activeRoundRect = 0;
        activeDrag = 0;
        filled = 0;
        break;
    case 6:
        activeDot = 0;
        activeLine = 0;
        activeCurve = 0;
        activeRect = 0;
        activeCircle = 1;
        activeRoundRect = 0;
        activeDrag = 0;
        filled = 1;
        break;
    case 7:
        activeDot = 0;
        activeLine = 0;
        activeCurve = 0;
        activeRect = 0;
        activeCircle = 0;
        activeRoundRect = 1;
        activeDrag = 0;
        filled = 0;
        break;
    case 8:
        activeDot = 0;
        activeLine = 0;
        activeCurve = 0;
        activeRect = 0;
        activeCircle = 0;
        activeRoundRect = 1;
        activeDrag = 0;
        filled = 1;
        break;
    case 9:
        activeDot = 0;
        activeLine = 0;
        activeCurve = 1;
        activeRect = 0;
        activeCircle = 0;
        activeRoundRect = 0;
        activeDrag = 0;
        break;
    case 10:
        activeDot = 0;
        activeLine = 0;
        activeCurve = 0;
        activeRect = 0;
        activeCircle = 0;
        activeRoundRect = 0;
        activeDrag = 1;
        break;
    default:
        break;
    }
}

void OGLWidget::chooseColor(float R, float G, float B)
{
    curColor.R = R;
    curColor.G = G;
    curColor.B = B;
}

void OGLWidget::chooseWidth(int index)
{
    switch(index){
    case 0:
        lineWidth = 1.0f;
        break;
    case 1:
        lineWidth = 5.0f;
        break;
    case 2:
        lineWidth = 8.0f;
        break;
    }
}
void OGLWidget::undo()
{
    if(!patternPainted.isEmpty()){
    switch(patternPainted.back()){
    case 2:
        if(!Llist.isEmpty()){
        Llisttmp.push_back(Llist.back());
        Llist.pop_back();
        }
        break;
    case 3:
        if(!Rlist.isEmpty()){
        Rlisttmp.push_back(Rlist.back());
        Rlist.pop_back();
        }
        break;
    case 5:
        if(!Clist.isEmpty()){
        Clisttmp.push_back(Clist.back());
        Clist.pop_back();
        }
        break;
    case 7:
        if(!RRlist.isEmpty()){
        RRlisttmp.push_back(RRlist.back());
        RRlist.pop_back();
        }
        break;
    case 9:
        if(!Curlist.isEmpty()){
        Curlisttmp.push_back(Curlist.back());
        Curlist.pop_back();
        }
        break;
    default:
        break;
    }
    patternPaintedR.push_back(patternPainted.back());
    patternPainted.pop_back();
    }
    activeDot = 0;
    activeLine = 0;
    activeCurve = 0;
    activeRect = 0;
    activeCircle = 0;
    activeRoundRect = 0;
    isRubber = 0;
    update();
}

void OGLWidget::redo()
{
    if(!patternPaintedR.isEmpty()){
    switch(patternPaintedR.back()){
    case 2:
        if(!Llisttmp.isEmpty()){
        Llist.push_back(Llisttmp.back());
        Llisttmp.pop_back();
        }
        break;
    case 3:
        if(!Rlisttmp.isEmpty()){
        Rlist.push_back(Rlisttmp.back());
        Rlisttmp.pop_back();
        }
        break;
    case 5:
        if(!Clisttmp.isEmpty()){
        Clist.push_back(Clisttmp.back());
        Clisttmp.pop_back();
        }
        break;
    case 7:
        if(!RRlisttmp.isEmpty()){
        RRlist.push_back(RRlisttmp.back());
        RRlisttmp.pop_back();
        }
        break;
    case 9:
        if(!Curlisttmp.isEmpty()){
        Curlist.push_back(Curlisttmp.back());
        Curlisttmp.pop_back();
        }
        break;
    default:
        break;
    }
    patternPainted.push_back(patternPaintedR.back());
    patternPaintedR.pop_back();
    }
    activeDot = 0;
    activeLine = 0;
    activeCurve = 0;
    activeRect = 0;
    activeCircle = 0;
    activeRoundRect = 0;
    isRubber = 0;
    update();
}

QMessageBox::StandardButton OGLWidget::clearScreen()
{
    QMessageBox::StandardButton judge = QMessageBox::warning(NULL, "警告", "确定要放弃编辑的内容吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(judge == QMessageBox::Yes){
        patternPainted.clear();patternPaintedR.clear();
        Dlist.clear();Dlisttmp.clear();
        Llist.clear();Llisttmp.clear();
        Rlist.clear();Rlisttmp.clear();
        RRlist.clear();RRlisttmp.clear();
        Clist.clear();Clisttmp.clear();
        Curlist.clear();Curlisttmp.clear();
        activeDot = 0;
        activeLine = 0;
        activeCurve = 0;
        activeRect = 0;
        activeCircle = 0;
        activeRoundRect = 0;
        isRubber = 0;
        glClear(GL_COLOR_BUFFER_BIT);
        update();
    }
    return judge;
}

void OGLWidget::printList()
{
    //Draw Rectangles
    glLineWidth(lineWidth);
    if(activeRect)
        printRects();
    for(int i=0;i<Rlist.length();i++){
        float x1 = Rlist[i].x1;
        float y1 = Rlist[i].y1;
        float x2 = Rlist[i].x2;
        float y2 = Rlist[i].y2;
        if(Rlist[i].released == 1){
            glColor3f(Rlist[i].c.R,Rlist[i].c.G,Rlist[i].c.B);
            glLineWidth(Rlist[i].w);
            if(Rlist[i].filled == 1)
                glRectf(x1, y1, x2, y2);
            else
                glEmptyRect(x1, y1, x2, y2);
            glFlush();
            rectReleased = 0;
        }
    }

    //Draw RoundRect
    glLineWidth(lineWidth);
    if(activeRoundRect)
        printRoundRect();
    for(int i=0;i<RRlist.length();i++){
        float x = RRlist[i].x;
        float y = RRlist[i].y;
        float w = RRlist[i].w;
        float h = RRlist[i].h;
        if(RRlist[i].released == 1){
            glColor3f(RRlist[i].c.R,RRlist[i].c.G,RRlist[i].c.B);
            glLineWidth(RRlist[i].wid);
            if(RRlist[i].filled == 1)
                glRoundRec(x,y,w,h,(w+h)/16,GL_POLYGON);
            else
                glRoundRec(x,y,w,h,(w+h)/16,GL_LINE_LOOP);
            glFlush();
            roundRectReleased = 0;
        }
    }

    //Draw Circles
    glLineWidth(lineWidth);
    if(activeCircle)
        printCirs();
    int n=100;
    for(int i=0;i<Clist.length();i++){
        float x1 = Clist[i].x1;
        float y1 = Clist[i].y1;
        float x2 = Clist[i].x2;
        float y2 = Clist[i].y2;
        if(Clist[i].released == 1){
            float R1=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/2;
            float centerx1 = (x1+x2)/2;
            float centery1 = (y1+y2)/2;
            glColor3f(Clist[i].c.R,Clist[i].c.G,Clist[i].c.B);
            glLineWidth(Clist[i].w);
            if(Clist[i].filled == 1)
                glBegin(GL_TRIANGLE_FAN);
            else
                glBegin(GL_LINE_LOOP);
            for(int i=0;i<n;i++)
                glVertex2f(centerx1+R1*cos(2*Pi/n*i), centery1+R1*sin(2*Pi/n*i));
            glEnd();
            cirReleased = 0;
        }
    }

    //Draw Curves
    glLineWidth(lineWidth);
    if(activeCurve)
        printCurves();
    curves tempCur;
    if(coor.length()==4){
        tempCur.x1=coor[0].first;tempCur.y1=coor[0].second;
        tempCur.x2=coor[1].first;tempCur.y2=coor[1].second;
        tempCur.x3=coor[2].first;tempCur.y3=coor[2].second;
        tempCur.x4=coor[3].first;tempCur.y4=coor[3].second;
        tempCur.c = curColor;
        tempCur.w = lineWidth;
        Curlist.push_back(tempCur);
        coor.clear();
    }
    for(int i=0;i<Curlist.length();i++){
        float x1=Curlist[i].x1;float y1=Curlist[i].y1;
        float x2=Curlist[i].x2;float y2=Curlist[i].y2;
        float x3=Curlist[i].x3;float y3=Curlist[i].y3;
        float x4=Curlist[i].x4;float y4=Curlist[i].y4;
        glColor3f(Curlist[i].c.R,Curlist[i].c.G,Curlist[i].c.B);
        glLineWidth(Curlist[i].w);
        Bezier(20, x1, y1, x2, y2, x3, y3, x4, y4);
    }

    //Draw Lines
    glLineWidth(lineWidth);
    if(activeLine)
        printLines();
    for(int i=0;i<Llist.length();i++){
        float x1 = Llist[i].x1;
        float y1 = Llist[i].y1;
        float x2 = Llist[i].x2;
        float y2 = Llist[i].y2;
        if(Llist[i].released == 1){
            glColor3f(Llist[i].c.R,Llist[i].c.G,Llist[i].c.B);
            glLineWidth(Llist[i].w);
            glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glEnd();
            glFlush();
            lineReleased = 0;
        }
    }

    //Draw Dots;
    if(activeDot)
        printDot();
    for(int i=0;i<Dlist.length();i++){
        float x = Dlist[i].dotx;
        float y = Dlist[i].doty;
        float s = Dlist[i].size;
        glPointSize(s);
        glColor3f(Dlist[i].c.R,Dlist[i].c.G,Dlist[i].c.B);
        glBegin(GL_POINTS);
        glVertex2f(x, y);
        glEnd();
        glFlush();
    }
}

void OGLWidget::printDot()
{
    glColor3f(curColor.R,curColor.G,curColor.B);
}

void OGLWidget::printLines()
{
    glColor3f(curColor.R,curColor.G,curColor.B);
    glBegin(GL_LINES);
    glVertex2f(lineX1, lineY1);
    glVertex2f(lineX2, lineY2);
    glEnd();
}

void OGLWidget::printCurves()
{
    glColor3f(curColor.R,curColor.G,curColor.B);
    for(int i=0;i<coor.length();i++){
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        glVertex2f(coor[i].first, coor[i].second);
        glEnd();
    }
    if(coor.length()==4){
        Bezier(20, coor[0].first, coor[0].second, coor[1].first, coor[1].second, coor[2].first, coor[2].second, coor[3].first, coor[3].second);
        patternPainted.push_back(9);
    }
}

void OGLWidget::printRects()
{
    glColor3f(curColor.R,curColor.G,curColor.B);
    if(filled)
        glRectf(RectX1, RectY1, RectX2, RectY2);
    else
        glEmptyRect(RectX1, RectY1, RectX2, RectY2);
    glFlush();
}

void OGLWidget::printCirs()
{
    glColor3f(curColor.R,curColor.G,curColor.B);
    int n=100;
    float R=sqrt((CirX1-CirX2)*(CirX1-CirX2)+(CirY1-CirY2)*(CirY1-CirY2))/2;
    float centerx = (CirX1+CirX2)/2;
    float centery = (CirY1+CirY2)/2;
    if(filled)
        glBegin(GL_TRIANGLE_FAN);
    else
        glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++)
        glVertex2f(centerx+R*cos(2*Pi/n*i), centery+R*sin(2*Pi/n*i));
    glEnd();
    glFlush();
}

void OGLWidget::printRoundRect()
{
    glColor3f(curColor.R,curColor.G,curColor.B);
    float centerX = (RRectX1+RRectX2)/2;
    float centerY = (RRectY1+RRectY2)/2;
    float width = fabs(RRectX1-RRectX2);
    float height = fabs(RRectY1-RRectY2);
    if(filled)
        glRoundRec(centerX,centerY,width,height,(width+height)/16,GL_POLYGON);
    else
        glRoundRec(centerX,centerY,width,height,(width+height)/16,GL_LINE_LOOP);
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1,1,1,1);
}

void OGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if(release)
        glClear(GL_COLOR_BUFFER_BIT);
    printList();
}

void OGLWidget::mousePressEvent(QMouseEvent *event)
{
    //Draw Dots
    if(activeDot)
        if(event->button() == Qt::LeftButton)
        {
            int wid = width()/2;
            int hei = height()/2;
            dotx = static_cast<float>(event->x()-wid)/wid;
            doty = static_cast<float>((2*hei-event->y())-hei)/hei;
            update();
        }

    //Draw Lines
    if(activeLine)
        if(event->button() == Qt::LeftButton)
        {
            release = 0;
            int wid = width()/2;
            int hei = height()/2;
            lineX1 = static_cast<float>(event->x()-wid)/wid;
            lineY1 = static_cast<float>((2*hei-event->y())-hei)/hei;
            patternPainted.push_back(2);
        }

    //Draw Curves
    if(activeCurve)
        if(event->button() == Qt::LeftButton)
        {
            release = 0;
            int wid = width()/2;
            int hei = height()/2;
            float x = static_cast<float>(event->x()-wid)/wid;
            float y = static_cast<float>((2*hei-event->y())-hei)/hei;
            coor.push_back(qMakePair(x, y));
            update();
        }

    //Draw Rectangles
    if(activeRect)
        if(event->button() == Qt::LeftButton)
        {
            release = 0;
            int wid = width()/2;
            int hei = height()/2;
            RectX1 = static_cast<float>(event->x()-wid)/wid;
            RectY1 = static_cast<float>((2*hei-event->y())-hei)/hei;
            patternPainted.push_back(3);
        }

    //Draw RoundRect
    if(activeRoundRect)
        if(event->button() == Qt::LeftButton)
        {
            release = 0;
            int wid = width()/2;
            int hei = height()/2;
            RRectX1 = static_cast<float>(event->x()-wid)/wid;
            RRectY1 = static_cast<float>((2*hei-event->y())-hei)/hei;
            patternPainted.push_back(7);
        }

    //Draw Circles
    if(activeCircle)
        if(event->button() == Qt::LeftButton)
        {
            release = 0;
            int wid = width()/2;
            int hei = height()/2;
            CirX1 = static_cast<float>(event->x()-wid)/wid;
            CirY1 = static_cast<float>((2*hei-event->y())-hei)/hei;
            patternPainted.push_back(5);
        }

    //DragSelected
    if(activeDrag)
        if(event->button() == Qt::LeftButton)
        {
            release = 0;
            selectedPattern = -1;
            selectedIndex = -1;
            int wid = width()/2;
            int hei = height()/2;
            float tDragX = static_cast<float>(event->x()-wid)/wid;
            float tDragY = static_cast<float>((2*hei-event->y())-hei)/hei;
            mouseMoveTempX = tDragX;
            mouseMoveTempY = tDragY;
            float minDist = INT_MAX, tempDist, tempX, tempY;
            //Line
            for(int i=0; i<Llist.size(); ++i){
                tempX = ((Llist[i].x1+Llist[i].x2)/2-tDragX)*((Llist[i].x1+Llist[i].x2)/2-tDragX);
                tempY = ((Llist[i].y1+Llist[i].y2)/2-tDragY)*((Llist[i].y1+Llist[i].y2)/2-tDragY);
                tempDist = sqrt(tempX+tempY);
                if(minDist > tempDist){
                    minDist = tempDist;
                    selectedPattern = 0;
                    selectedIndex = i;
                }
            }
            //Curve
            for(int i=0; i<Curlist.size(); ++i){
                tempX = ((Curlist[i].x1+Curlist[i].x3)/2-tDragX)*((Curlist[i].x1+Curlist[i].x3)/2-tDragX);
                tempY = ((Curlist[i].y1+Curlist[i].y3)/2-tDragY)*((Curlist[i].y1+Curlist[i].y3)/2-tDragY);
                tempDist = sqrt(tempX+tempY);
                if(minDist > tempDist){
                    minDist = tempDist;
                    selectedPattern = 1;
                    selectedIndex = i;
                }
            }
            //Rect
            for(int i=0; i<Rlist.size(); ++i){
                tempX = ((Rlist[i].x1+Rlist[i].x2)/2-tDragX)*((Rlist[i].x1+Rlist[i].x2)/2-tDragX);
                tempY = ((Rlist[i].y1+Rlist[i].y2)/2-tDragY)*((Rlist[i].y1+Rlist[i].y2)/2-tDragY);
                tempDist = sqrt(tempX+tempY);
                if(minDist > tempDist){
                    minDist = tempDist;
                    selectedPattern = 2;
                    selectedIndex = i;
                }
            }
            //RoundRect
            for(int i=0; i<RRlist.size(); ++i){
                tempX = (RRlist[i].x-tDragX)*(RRlist[i].x-tDragX);
                tempY = (RRlist[i].y-tDragY)*(RRlist[i].y-tDragY);
                tempDist = sqrt(tempX+tempY);
                if(minDist > tempDist){
                    minDist = tempDist;
                    selectedPattern = 3;
                    selectedIndex = i;
                }
            }
            //Circle
            for(int i=0; i<Clist.size(); ++i){
                tempX = ((Clist[i].x1+Clist[i].x2)/2-tDragX)*((Clist[i].x1+Clist[i].x2)/2-tDragX);
                tempY = ((Clist[i].y1+Clist[i].y2)/2-tDragY)*((Clist[i].y1+Clist[i].y2)/2-tDragY);
                tempDist = sqrt(tempX+tempY);
                if(minDist > tempDist){
                    minDist = tempDist;
                    selectedPattern = 4;
                    selectedIndex = i;
                }
            }
        }
}

void OGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //Draw Lines
    if(activeLine)
        if(event->button() == Qt::LeftButton)
        {
            release = 1;
            int wid = width()/2;
            int hei = height()/2;
            lineX3 = static_cast<float>(event->x()-wid)/wid;
            lineY3 = static_cast<float>((2*hei-event->y())-hei)/hei;
            lineReleased = 1;
            lines tempL;
            tempL.x1 = lineX1;
            tempL.x2 = lineX3;
            tempL.y1 = lineY1;
            tempL.y2 = lineY3;
            tempL.c = curColor;
            tempL.released = lineReleased;
            tempL.w = lineWidth;
            int mark = 1;
            for(int i=0; i<Llist.size(); ++i){
                if(tempL.x1 + tempL.x2 + tempL.y1 + tempL.y2 > 4
                        || (Llist[i].x1 == tempL.x1 && Llist[i].x2 == tempL.x2 && Llist[i].y1 == tempL.y1 && Llist[i].y2 == tempL.y2)){
                    mark = 0;
                    break;
                }
            }
            if(mark && tempL.released == 1)
                Llist.push_back(tempL);
            _init();
            update();
        }

    //Draw Rectangles
    if(activeRect)
        if(event->button() == Qt::LeftButton)
        {
            release = 1;
            int wid = width()/2;
            int hei = height()/2;
            RectX3 = static_cast<float>(event->x()-wid)/wid;
            RectY3 = static_cast<float>((2*hei-event->y())-hei)/hei;
            rectReleased = 1;
            Rects tempR;
            tempR.x1 = RectX1;
            tempR.x2 = RectX3;
            tempR.y1 = RectY1;
            tempR.y2 = RectY3;
            tempR.c = curColor;
            tempR.released = rectReleased;
            tempR.filled = filled;
            tempR.w = lineWidth;
            int mark = 1;
            for(int i=0; i<Rlist.size(); ++i){
                if(Rlist[i].x1 == tempR.x1 && Rlist[i].x2 == tempR.x2 && Rlist[i].y1 == tempR.y1 && Rlist[i].y2 == tempR.y2){
                    mark = 0;
                    break;
                }
            }
            if(mark && tempR.released)
                Rlist.push_back(tempR);
            _init();
            update();
        }

    //Draw RoundRect
    if(activeRoundRect)
    {
        if(event->button() == Qt::LeftButton){
            release = 1;
            int wid = width()/2;
            int hei = height()/2;
            RRectX3 = static_cast<float>(event->x()-wid)/wid;
            RRectY3 = static_cast<float>((2*hei-event->y())-hei)/hei;
            roundRectReleased = 1;
            RoundRect tempRR;
            tempRR.x = (RRectX1+RRectX3)/2;
            tempRR.y = (RRectY1+RRectY3)/2;
            tempRR.w = fabs(RRectX1-RRectX3);
            tempRR.h = fabs(RRectY1-RRectY3);
            tempRR.c = curColor;
            tempRR.released = roundRectReleased;
            tempRR.filled = filled;
            tempRR.wid = lineWidth;
            int mark = 1;
            for(int i=0; i<RRlist.size(); ++i){
                if(RRlist[i].x == tempRR.x && RRlist[i].y == tempRR.y){
                    mark = 0;
                    break;
                }
            }
            if(mark && tempRR.released)
                RRlist.push_back(tempRR);
            _init();
            update();
        }
    }

    //Draw Circles
    if(activeCircle)
        if(event->button() == Qt::LeftButton)
        {
            release = 1;
            int wid = width()/2;
            int hei = height()/2;
            CirX3 = static_cast<float>(event->x()-wid)/wid;
            CirY3 = static_cast<float>((2*hei-event->y())-hei)/hei;
            cirReleased = 1;
            Circles tempC;
            int n=100;
            tempC.x1 = CirX1;
            tempC.x2 = CirX3;
            tempC.y1 = CirY1;
            tempC.y2 = CirY3;
            tempC.c = curColor;
            tempC.released = cirReleased;
            tempC.filled = filled;
            tempC.w = lineWidth;
            int mark = 1;
            for(int i=0; i<Clist.size(); ++i){
                if(Clist[i].x1 == tempC.x1 && Clist[i].x2 == tempC.x2 && Clist[i].y1 == tempC.y1 && Clist[i].y2 == tempC.y2){
                    mark = 0;
                    break;
                }
            }
            if(mark && tempC.released)
                Clist.push_back(tempC);
            _init();
            update();
        }
}

void OGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    //Draw Dots
    if(activeDot)
    {
        int wid = width()/2;
        int hei = height()/2;
        dotx = static_cast<float>(event->x()-wid)/wid;
        doty = static_cast<float>((2*hei-event->y())-hei)/hei;
        dots tempD;
        tempD.dotx = dotx;
        tempD.doty = doty;
        tempD.c = curColor;
        if(isRubber)
            tempD.size = 15.0f;
        else
            tempD.size = 5.0f;
        int mark = 1;
        for(int i=0; i<Dlist.size(); ++i){
            if(tempD.dotx + tempD.doty > 2 || (Dlist[i].dotx == tempD.dotx && Dlist[i].doty == tempD.doty)){
                mark = 0;
                break;
            }
        }
        if(mark)
            Dlist.push_back(tempD);
        update();
    }

    //Draw Lines
    if(activeLine)
    {
        int wid = width()/2;
        int hei = height()/2;
        lineX2 = static_cast<float>(event->x()-wid)/wid;
        lineY2 = static_cast<float>((2*hei-event->y())-hei)/hei;
        update();
    }

    //Draw Rectangles
    if(activeRect)
    {
        int wid = width()/2;
        int hei = height()/2;
        RectX2 = static_cast<float>(event->x()-wid)/wid;
        RectY2 = static_cast<float>((2*hei-event->y())-hei)/hei;
        update();
    }

    //Draw RoundRect
    if(activeRoundRect)
    {
        int wid = width()/2;
        int hei = height()/2;
        RRectX2 = static_cast<float>(event->x()-wid)/wid;
        RRectY2 = static_cast<float>((2*hei-event->y())-hei)/hei;
        update();
    }

    //Draw Circles
    if(activeCircle)
    {
        int wid = width()/2;
        int hei = height()/2;
        CirX2 = static_cast<float>(event->x()-wid)/wid;
        CirY2 = static_cast<float>((2*hei-event->y())-hei)/hei;
        update();
    }

    //Drag
    if(activeDrag)
    {
        int wid = width()/2;
        int hei = height()/2;
        DragX = static_cast<float>(event->x()-wid)/wid;
        DragY = static_cast<float>((2*hei-event->y())-hei)/hei;
        switch (selectedPattern) {
        case 0:
            Llist[selectedIndex].x1 += DragX - mouseMoveTempX;
            Llist[selectedIndex].x2 += DragX - mouseMoveTempX;
            Llist[selectedIndex].y1 += DragY - mouseMoveTempY;
            Llist[selectedIndex].y2 += DragY - mouseMoveTempY;
            mouseMoveTempX = DragX;
            mouseMoveTempY = DragY;
            break;
        case 1:
            Curlist[selectedIndex].x1 += DragX - mouseMoveTempX;
            Curlist[selectedIndex].x2 += DragX - mouseMoveTempX;
            Curlist[selectedIndex].x3 += DragX - mouseMoveTempX;
            Curlist[selectedIndex].x4 += DragX - mouseMoveTempX;
            Curlist[selectedIndex].y1 += DragY - mouseMoveTempY;
            Curlist[selectedIndex].y2 += DragY - mouseMoveTempY;
            Curlist[selectedIndex].y3 += DragY - mouseMoveTempY;
            Curlist[selectedIndex].y4 += DragY - mouseMoveTempY;
            mouseMoveTempX = DragX;
            mouseMoveTempY = DragY;
            break;
        case 2:
            Rlist[selectedIndex].x1 += DragX - mouseMoveTempX;
            Rlist[selectedIndex].x2 += DragX - mouseMoveTempX;
            Rlist[selectedIndex].y1 += DragY - mouseMoveTempY;
            Rlist[selectedIndex].y2 += DragY - mouseMoveTempY;
            mouseMoveTempX = DragX;
            mouseMoveTempY = DragY;
            break;
        case 3:
            RRlist[selectedIndex].x += DragX - mouseMoveTempX;
            RRlist[selectedIndex].y += DragY - mouseMoveTempY;
            mouseMoveTempX = DragX;
            mouseMoveTempY = DragY;
            break;
        case 4:
            Clist[selectedIndex].x1 += DragX - mouseMoveTempX;
            Clist[selectedIndex].x2 += DragX - mouseMoveTempX;
            Clist[selectedIndex].y1 += DragY - mouseMoveTempY;
            Clist[selectedIndex].y2 += DragY - mouseMoveTempY;
            mouseMoveTempX = DragX;
            mouseMoveTempY = DragY;
            break;
        default:
            break;
        }
        update();
    }
}

void OGLWidget::resizeGL(int w, int h)
{

}
