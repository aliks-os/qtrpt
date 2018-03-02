/*
Name: QtRpt
Version: 2.0.1
Web-site: http://www.qtrpt.tk
Programmer: Aleksey Osipov
E-mail: aliks-os@ukr.net
Web-site: http://www.aliks-os.tk

Copyright 2012-2017 Aleksey Osipov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "RptFieldObject.h"

/*!
 \class RptFieldObject
 \inmodule RptFieldObject.cpp
 \brief RptFieldObject represent field of the report. On RptBandObject the RptFieldObject are placed

  The inner structure of report is following:
  \code
  QtRPT
    RptPageObject
      RptBandObject
        RptFieldObject
  \endcode
  There are possible to have some RptBandObject on the report's page but different type.
*/

/*!
 \variable RptFieldObject::name
 \brief The name of field.
*/

/*!
 \variable RptFieldObject::value
 \brief The value of field.
*/

/*!
 \variable RptFieldObject::rect
 \brief Rectangle of the field.
*/

/*!
 \variable RptFieldObject::borderTop
 \brief Top's border color.
 \sa borderColor
*/

/*!
 \variable RptFieldObject::borderBottom
 \brief Bottom's border color.
 \sa borderColor
*/

/*!
 \variable RptFieldObject::borderLeft
 \brief Left's border color.
 \sa borderColor
*/

/*!
 \variable RptFieldObject::borderRight
 \brief Right's border color.
 \sa borderColor
*/

/*!
 \variable RptFieldObject::borderColor
 \brief Common border color for all sides.
*/

/*!
 \variable RptFieldObject::fontColor
 \brief Current font color. Default is Qt::black
*/

/*!
 \variable RptFieldObject::backgroundColor
 \brief Current background color. Default is Qt::white
*/

/*!
 \variable RptFieldObject::borderWidth
 \brief Border's width. Default value is 1px.
*/

/*!
 \variable RptFieldObject::autoHeight
 \brief Auto height of field. Default value is false.
 \note Applicable only for fields which placed on MasterDataBand.
*/

/*!
 \variable RptFieldObject::textWrap
 \brief Text wrap of field. Default value is true.
 \note For type Text only.
*/

/*!
 \variable RptFieldObject::aligment
 \brief Aligment of text.
*/

/*!
 \variable RptFieldObject::borderStyle
 \brief Border's style.
 \list
   \li solid
   \li dashed
   \li dotted
   \li dot-dash
   \li dot-dot-dash
 \endlist
*/

/*!
 \variable RptFieldObject::font
 \brief Font of the Text field.
*/

/*!
 \variable RptFieldObject::fieldType
 \brief Type of the field.
 \sa QtRptName::FieldType
*/

/*!
 \variable RptFieldObject::formatString
 \brief Format of number value.
*/

/*!
 \variable RptFieldObject::highlighting
 \brief Encoded string containing the conditions of highlighting.
*/

/*!
 \variable RptFieldObject::imgFormat
 \brief Extension of image format.
 \note For type Image only.
*/

/*!
 \variable RptFieldObject::printing
 \brief Mark of printing.
*/

/*!
 \variable RptFieldObject::barcodeType
 \brief Type of the barcode.
 \note For type Barcode only.
*/

/*!
 \variable RptFieldObject::barcodeFrameType
 \brief Type of the barcode's frame.
 \list
   \li 0 - no border
   \li 1 - bind
   \li 2 - box
 \endlist
 \note For type Barcode only.
*/

/*!
 \variable RptFieldObject::barcodeHeight
 \brief Height of Barcode.
 \note For type Barcode only.
*/

/*!
 \variable RptFieldObject::ignoreAspectRatio
 \brief Ignore or not aspect ratio for image.
 \note For type Image only.
*/

/*!
 \variable RptFieldObject::picture
 \brief String, which must contains 84 bit base array.
 \note For type Image only.
*/

/*!
 \variable RptFieldObject::parentBand
 \brief Pointer to the parent band.
 \sa RptBandObject
*/

/*!
 \variable RptFieldObject::lineStartX
 \brief X of line start.
 \note For type Line only.
*/

/*!
 \variable RptFieldObject::lineEndX
 \brief X of line end.
 \note For type Line only.
*/

/*!
 \variable RptFieldObject::lineStartY
 \brief Y of line start.
 \note For type Line only.
*/

/*!
 \variable RptFieldObject::lineEndY
 \brief Y of line end.
 \note For type Line only.
*/

/*!
 \variable RptFieldObject::arrowStart
 \brief Draw arrow at the start.
 \note For type Line only.
*/

/*!
 \variable RptFieldObject::arrowEnd
 \brief Draw arrow at the end.
 \note For type Line only.
*/

/*!
 \variable RptFieldObject::showGrid
 \brief Show or not grid at diagram.
 \note For type Diagram only.
*/

/*!
 \variable RptFieldObject::showLegend
 \brief Show or not legend at diagram.
 \note For type Diagram only.
*/

/*!
 \variable RptFieldObject::showCaption
 \brief Show or not caption at diagram.
 \note For type Diagram only.
 \sa showGraphCaption
*/

/*!
 \variable RptFieldObject::showGraphCaption
 \brief Show or not legend at caption for each graph.
 \note For type Diagram only.
 \sa showCaption
*/

/*!
 \variable RptFieldObject::showPercent
 \brief Show persent value or show absolute.
 \note For type Diagram only.
*/

/*!
 \variable RptFieldObject::autoFillData
 \brief Automatic fill diagram from certian data or manual filling.
 \note For type Diagram only.
*/

/*!
 \variable RptFieldObject::caption
 \brief String represents the caption.
 \note For type Diagram only.
*/

/*!
 \variable RptFieldObject::graphList
 \brief List containing GraphParam which holds data for each Graph.
 \note For type Diagram only.
*/

/*!
 \fn int RptFieldObject::recNo()
    \c Return a current record number.
*/

/*!
 \fn int RptFieldObject::reportPage()
    \c Return a current Report page number.
*/

/*!
 \fn RptFieldObject::RptFieldObject()
    Constructs a RptFieldObject object.
*/
RptFieldObject::RptFieldObject()
{
    this->highlighting = "";
    this->autoHeight = false;
    this->backgroundColor = Qt::white;
    this->m_backgroundColor = Qt::white;
    this->fontColor = Qt::black;
    this->m_fontColor = Qt::black;
    QFont font;
    font.setFamily(font.defaultFamily());
    font.setPointSize(12);
    this->font = font;
    this->printing = "1";
    this->borderWidth = 1;
    this->borderColor = Qt::black;
    this->borderBottom = Qt::black;
    this->borderRight = Qt::black;
    this->borderLeft = Qt::black;
    this->borderTop = Qt::black;
    this->aligment = Qt::AlignVCenter | Qt::AlignLeft;
    this->parentBand = nullptr;
    this->parentCrossTab = nullptr;
}

/*!
 \fn RptFieldObject::~RptFieldObject()
    Destructs a RptFieldObject object.
*/
RptFieldObject::~RptFieldObject()
{
    if (fieldType == CrossTab)
        delete crossTab;
}

/*!
 \fn void RptFieldObject::setDefaultFontColor(QColor value)
    Sets default font color with \a value.
*/
void RptFieldObject::setDefaultFontColor(QColor value)
{
    fontColor = value;
    m_fontColor = value;
}

/*!
 \fn void RptFieldObject::setDefaultBackgroundColor(QColor value)
    Sets default background color with \a value.
*/
void RptFieldObject::setDefaultBackgroundColor(QColor value)
{
    backgroundColor = value;
    m_backgroundColor = value;
}

void RptFieldObject::setProperty(QtRPT *qtrpt, QDomElement e)
{
    m_qtrpt = qtrpt;
    highlighting = e.attribute("highlighting","");
    printing = e.attribute("printing","1");
    name = e.attribute("name");
    value = e.attribute("value");
    rect.setX(e.attribute("left").toInt());
    rect.setY(e.attribute("top").toInt());
    rect.setWidth((e.attribute("width").toInt()));
    rect.setHeight(e.attribute("height").toInt());
    borderTop = colorFromString(e.attribute("borderTop"));
    borderBottom = colorFromString(e.attribute("borderBottom"));
    borderLeft = colorFromString(e.attribute("borderLeft"));
    borderRight = colorFromString(e.attribute("borderRight"));
    borderWidth = e.attribute("borderWidth","1").replace("px","").toInt();
    borderStyle = e.attribute("borderStyle","solid");
    borderColor = colorFromString(e.attribute("borderColor"));

    rotate = e.attribute("rotate","0").toInt();

    aligment = QtRPT::getAligment(e);
    autoHeight = e.attribute("autoHeight","0").toInt();

    QFont m_font(e.attribute("fontFamily"),e.attribute("fontSize").toInt());
    m_font.setBold(e.attribute("fontBold").toInt());
    m_font.setItalic(e.attribute("fontItalic").toInt());
    m_font.setUnderline(e.attribute("fontUnderline").toInt());
    m_font.setStrikeOut(e.attribute("fontStrikeout").toInt());
    font = m_font;

    backgroundColor = colorFromString(e.attribute("backgroundColor"));
    m_backgroundColor = backgroundColor;
    fontColor = colorFromString(e.attribute("fontColor"));
    m_fontColor = fontColor;

    imgFormat = e.attribute("imgFormat","PNG");
    textWrap = e.attribute("textWrap","1").toInt();

    fieldType = qtrpt->getFieldType(e);
    formatString = e.attribute("format","");

    barcodeType = e.attribute("barcodeType","13").toInt();
    barcodeFrameType = e.attribute("barcodeFrameType","0").toInt();
    barcodeHeight = e.attribute("barcodeHeight","50").toInt();

    picture = QByteArray::fromBase64(e.attribute("picture","text").toLatin1());
    ignoreAspectRatio = e.attribute("ignoreAspectRatio","1").toInt();

    showGrid = e.attribute("showGrid","1").toInt();
    showLegend = e.attribute("showLegend","1").toInt();
    showCaption = e.attribute("showCaption","1").toInt();
    showGraphCaption = e.attribute("showGraphCaption","1").toInt();
    showPercent = e.attribute("showPercent","1").toInt();
    caption = e.attribute("caption","Example");
    autoFillData = e.attribute("autoFillData","0").toInt();

    lineStartX = e.attribute("lineStartX").toInt();
    lineEndX = e.attribute("lineEndX").toInt();
    lineStartY = e.attribute("lineStartY").toInt();
    lineEndY = e.attribute("lineEndY").toInt();
    arrowStart = e.attribute("arrowStart","0").toInt();
    arrowEnd = e.attribute("arrowEnd","0").toInt();

    if (fieldType == Diagram) {
        if (autoFillData == 1) {
            QDomNode g = e.firstChild();
            while(!g.isNull()) {
                QDomElement ge = g.toElement();

                GraphParam param;
                param.color = colorFromString( ge.attribute("color") );
                param.valueReal = qtrpt->sectionField(this->parentBand, ge.attribute("value"), false).toFloat();
                param.formula = ge.attribute("value");
                param.caption = ge.attribute("caption");
                graphList.append(param);

                g = g.nextSibling();
            }
        }
    }

    if (fieldType == CrossTab) {
        crossTab = new RptCrossTabObject();
        crossTab->rect = this->rect;
        crossTab->parentField = this;
        crossTab->loadParamFromXML(e);
    }
}

void RptFieldObject::updateHighlightingParam()
{
    QFont m_font(font);
    m_font.setBold(m_qtrpt->processHighligthing(this, FntBold).toInt());
    m_font.setItalic(m_qtrpt->processHighligthing(this, FntItalic).toInt());
    m_font.setUnderline(m_qtrpt->processHighligthing(this, FntUnderline).toInt());
    m_font.setStrikeOut(m_qtrpt->processHighligthing(this, FntStrikeout).toInt());
    font = m_font;

    backgroundColor = colorFromString(m_qtrpt->processHighligthing(this, BgColor).toString());
    fontColor = colorFromString(m_qtrpt->processHighligthing(this, FntColor).toString());
}

void RptFieldObject::updateDiagramValue()
{
    if (autoFillData == 1)
        for (auto &graph : graphList)
            graph.valueReal = m_qtrpt->sectionField(this->parentBand, graph.formula, false).toFloat();
}

/*!
 \fn RptFieldObject *RptFieldObject::clone()
    Clone the current field and return \c RptFieldObject of the new field object
*/
RptFieldObject *RptFieldObject::clone()
{
    auto field = new RptFieldObject();
    field->name = name;
    field->value = value;
    field->rect = rect;
    field->borderTop = borderTop;
    field->borderBottom = borderBottom;
    field->borderLeft = borderLeft;
    field->borderRight = borderRight;
    field->borderColor = borderColor;
    field->fontColor = fontColor;
    field->backgroundColor = backgroundColor;
    field->autoHeight = autoHeight;


    field->borderWidth = borderWidth;
    field->autoHeight = autoHeight;
    field->textWrap = textWrap;
    field->rotate = rotate;

    field->aligment = aligment;
    field->borderStyle = borderStyle;
    field->font = font;
    field->fieldType = fieldType;
    field->formatString = formatString;
    field->highlighting = highlighting;
    field->imgFormat = imgFormat;
    field->printing = printing;
    field->barcodeType = barcodeType;
    field->barcodeFrameType = barcodeFrameType;
    field->barcodeHeight = barcodeHeight;
    field->ignoreAspectRatio = ignoreAspectRatio;
    field->picture = picture;
    field->parentBand = parentBand;
    //field->*parentCrossTab = parentCrossTab;

    field->lineStartX = lineStartX;
    field->lineEndX = lineEndX;
    field->lineStartY = lineStartY;
    field->lineEndY = lineEndY;
    field->arrowStart = arrowStart;
    field->arrowEnd = arrowEnd;

    field->m_fontColor = m_fontColor;
    field->m_backgroundColor = m_backgroundColor;
    field->m_recNo = m_recNo;
    field->m_reportPage = m_reportPage;
    field->m_top = m_top;
    field->m_qtrpt = m_qtrpt;


    return field;
}

/*!
 \fn RptFieldObject::isCrossTabChild()
    Return true if the field is a part of CrossTabObject.
*/
bool RptFieldObject::isCrossTabChild()
{
    return this->parentCrossTab != nullptr;
}

/*!
 \fn void RptFieldObject::setTop(int top)
    Sets \a top of field.

    \sa rect
*/
void RptFieldObject::setTop(int top)
{
    m_top = top;
}

/*!
 \fn QString RptFieldObject::getHTMLStyle()
    Return HTML representation of the field.
*/
QString RptFieldObject::getHTMLStyle()
{
    QString style;

    QString alig;
    if (this->aligment &Qt::AlignRight) alig = "right";
    if (this->aligment &Qt::AlignLeft) alig = "left";
    if (this->aligment &Qt::AlignHCenter) alig = "center";
    if (this->aligment &Qt::AlignJustify) alig = "justify";

    if (this->autoHeight == 1)
        this->rect.setHeight(parentBand->realHeight);

    if (fieldType == Text) {
        style = "style='color:"+this->fontColor.name()+";"+
                "background:"+this->backgroundColor.name()+";"+
                "border-left: solid thin "+this->borderLeft.name()+";"+
                "border-right: solid thin "+this->borderRight.name()+";"+
                "border-top: solid thin "+this->borderTop.name()+";"+
                "border-bottom: solid thin "+this->borderBottom.name()+";"+
                "text-align:"+alig+";"+
                "font-size:"+QString::number(font.pointSize()+5)+"px;"+
                "position: absolute; left: "+QString::number(this->rect.x())+";"+
                "top: "+QString::number(this->m_top)+";"+
                "width: "+QString::number(this->rect.width())+";"+
                "height: "+QString::number(this->rect.height())+";";
        if (font.bold() == true)
            style += "font-weight: bold;";
        if (font.italic() == true)
            style += "font-style: italic;";
        style += "'";
    }

    if (fieldType == TextImage || fieldType == Image || fieldType == DatabaseImage) {
        double dblAspectRatio = 0;
        int nHeight = this->rect.height();
        int nWidth = this->rect.height();

        if (this->rect.height())
            dblAspectRatio = (double)this->rect.width() / (double)this->rect.height();

        if (dblAspectRatio) {
            nWidth = ((int)rint(nHeight * dblAspectRatio)) & -3;

            if (nWidth > this->rect.width()) {
                nWidth = this->rect.width();
                nHeight = ((int)rint(nWidth / dblAspectRatio)) & -3;
            }
        }

        style = "<div style='"
                "position: absolute; left: "+QString::number(this->rect.x())+";"+
                "top: "+QString::number(this->m_top)+";"+
                "width: "+QString::number(this->rect.width())+";"+
                "height: "+QString::number(this->rect.height())+";"+
                "text-align:"+alig+";"+
                "'>"+
                "<img "
                "width="+QString::number(nWidth)+" "
                "height="+QString::number(nHeight)+" "+
                "src=\"data:image/png;base64,"+this->picture.toBase64()+"\" /></div>\n";
    }

    return style;
}

QDebug operator<<(QDebug dbg, const RptFieldObject &obj)
{
    dbg << obj.name;
    return dbg;
}

QDebug operator<<(QDebug dbg, const RptFieldObject *obj)
{
    return dbg << (*obj).name;
}
