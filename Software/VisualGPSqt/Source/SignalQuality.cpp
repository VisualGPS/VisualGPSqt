/*
* MIT License
*
*  Copyright (c) 2018 VisualGPS, LLC
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*
*/
#include <QtCore>
#include <QtGui>
#include <map>
#include "SignalQuality.h"

CSignalQuality::CSignalQuality(CNMEAParserQt *pNMEAParser, QWidget *parent) :
    QWidget(parent),
    m_pNMEAParser(pNMEAParser)
{
    connect(pNMEAParser, SIGNAL(NewPositionUpdateGPS()), SLOT(OnNewPositionUpdateGPS()));
}

void CSignalQuality::OnNewPositionUpdateGPS()
{
    repaint();
}

void CSignalQuality::paintEvent(QPaintEvent */*event*/){
    DrawScreen();
}

void CSignalQuality::ConsolidateSatData(std::map <std::string, SAT_INFO_T>& mapSatData) {

    mapSatData.clear();

    //
    // Get GPS/GNSS information
    //
    // GPS
    CNMEAParserData::GSA_DATA_T gpgsaData;
    CNMEAParserData::GSV_DATA_T gpgsvData;
    m_pNMEAParser->GetGPGSA(gpgsaData);
    m_pNMEAParser->GetGPGSV(gpgsvData);
    // GNSS (So far, have not seen a GNSGV)
    CNMEAParserData::GSA_DATA_T gngsaData;
    m_pNMEAParser->GetGNGSA(gngsaData);
    // GLONASS
    CNMEAParserData::GSA_DATA_T glgsaData;
    CNMEAParserData::GSV_DATA_T glgsvData;
    m_pNMEAParser->GetGLGSA(glgsaData);
    m_pNMEAParser->GetGLGSV(glgsvData);
    // GALILEO
    CNMEAParserData::GSV_DATA_T gagsvData;
    CNMEAParserData::GSA_DATA_T gagsaData;
    m_pNMEAParser->GetGAGSA(gagsaData);
    m_pNMEAParser->GetGAGSV(gagsvData);


    // First we'll go through all of the GSV data and then we'll proceed
    // to the GSA data.
    SAT_INFO_T satInfo;
    for(int i = 0; i < CNMEAParserData::c_nMaxConstellation; i++) {
        // GPS
        if(gpgsvData.SatInfo[i].nPRN != CNMEAParserData::c_nInvlidPRN) {
            memset(&satInfo, 0, sizeof(satInfo));
            satInfo.nSNR = gpgsvData.SatInfo[i].nSNR;
            satInfo.nPRN = gpgsvData.SatInfo[i].nPRN;

            // GPS
            if( satInfo.nPRN >= NP_GPS_MIN_PRN && satInfo.nPRN <= NP_WAAS_MAX_PRN) {
                satInfo.nConstType = CT_GPS;
            }
            // GLONASS
            else if( satInfo.nPRN >= NP_GLONASS_MIN_PRN && satInfo.nPRN <= NP_GLONASS_MAX_PRN){
                satInfo.nConstType = CT_GLONASS;
            }

            satInfo.strNmeaSpec = "GP" +  std::to_string(gpgsvData.SatInfo[i].nPRN);
            mapSatData[satInfo.strNmeaSpec] = satInfo;
        }
        // Galileo
        if(gagsvData.SatInfo[i].nPRN != CNMEAParserData::c_nInvlidPRN) {
            memset(&satInfo, 0, sizeof(satInfo));
            satInfo.nSNR = gagsvData.SatInfo[i].nSNR;
            satInfo.nPRN = gagsvData.SatInfo[i].nPRN;
            satInfo.nConstType = CT_GALILEO;
            satInfo.strNmeaSpec = "EU" +  std::to_string(gagsvData.SatInfo[i].nPRN);
            mapSatData[satInfo.strNmeaSpec] = satInfo;
        }
        // GLONASS
        if(glgsvData.SatInfo[i].nPRN != CNMEAParserData::c_nInvlidPRN) {
            memset(&satInfo, 0, sizeof(satInfo));
            satInfo.nSNR = glgsvData.SatInfo[i].nSNR;
            satInfo.nPRN = glgsvData.SatInfo[i].nPRN;
            satInfo.nConstType = CT_GLONASS;
            satInfo.strNmeaSpec = "GP" +  std::to_string(glgsvData.SatInfo[i].nPRN);
            mapSatData[satInfo.strNmeaSpec] = satInfo;
        }
    }


    // GSA (figure out what satellites are used for navigagtion solution)
    // GPS
    for(int i = 0; i < CNMEAParserData::c_nMaxGSASats; i++) {
        if(gpgsaData.pnPRN[i] != CNMEAParserData::c_nInvlidPRN) {
            std::string strNmeaSpec = "GP" +  std::to_string(gpgsaData.pnPRN[i]);
            mapSatData[strNmeaSpec].bUsedForNav = true;
        }
    }

    // Galileo
    for(int i = 0; i < CNMEAParserData::c_nMaxGSASats; i++) {
        if(gagsaData.pnPRN[i] != CNMEAParserData::c_nInvlidPRN) {
            std::string strNmeaSpec = "EU" +  std::to_string(gagsaData.pnPRN[i]);
            mapSatData[strNmeaSpec].bUsedForNav = true;
        }
    }

    // GLONASS
    for(int i = 0; i < CNMEAParserData::c_nMaxConstellation; i++) {
        if(glgsaData.pnPRN[i] != CNMEAParserData::c_nInvlidPRN) {
            std::string strNmeaSpec = "GP" +  std::to_string(glgsaData.pnPRN[i]);
            mapSatData[strNmeaSpec].bUsedForNav = true;
        }
    }
    // GN
    for(int i = 0; i < CNMEAParserData::c_nMaxConstellation; i++) {
        if(gngsaData.pnPRN[i] != CNMEAParserData::c_nInvlidPRN) {
            std::string strNmeaSpec = "GP" +  std::to_string(gngsaData.pnPRN[i]);
            mapSatData[strNmeaSpec].bUsedForNav = true;


//             satInfo.nConstType = CT_GNSS;
//             satInfo.strNmeaSpec = strNmeaSpec;
//             mapSatData[strNmeaSpec] = satInfo;
//             mapSatData[strNmeaSpec].bUsedForNav = true;
        }
    }
}

void CSignalQuality::DrawScreen() {

    QPainter painter(this);
    QPalette pal;

    std::map <std::string, SAT_INFO_T> mapSatData;
    ConsolidateSatData(mapSatData);

    //
    // Erase background
    //
    painter.setPen(Qt::NoPen);
    painter.setBrush(pal.color(QPalette::Dark));
    painter.drawRect(0, 0, width(), height());

    int nTotalSats = static_cast<int>(mapSatData.size());

    //
    // Creaate used in nav database. Use PRN as index
    //
    //bool bUsedForNavagation[c_nMaxChannels];
    std::map <int, bool> bUsedForNavagation;

    //
    // Figure out signal quality bar width
    //
    qreal dWidth = 0;
    if(nTotalSats > 0) {
        dWidth = static_cast<qreal>(width()) / static_cast<qreal>(nTotalSats);
    }

    //
    // Create font - size it to the sig qual bar width
    //
    int nSize = static_cast<int>( dWidth * 0.3 );
    if(nSize > 20) nSize = 20;
    QFont Font("Helvetica [Cronyx]", nSize);
    painter.setFont(Font);

    //
    // Create the background sig qual rectangle. Leave room at bottom for
    // PRN
    //
    QFontMetrics fontMetrics(Font);
    qreal dPRNTextBoxHeight = static_cast<qreal>(fontMetrics.height()) * 1.25;
    QRectF rect(0, 0, dWidth, height() - dPRNTextBoxHeight);
    qreal x = 0;

    for (std::map<std::string, SAT_INFO_T>::iterator it=mapSatData.begin(); it!=mapSatData.end(); ++it) {
        SAT_INFO_T satInfo = it->second;
        //
        // Draw background of signal quality
        //
        painter.setPen(pal.color(QPalette::Dark));
        painter.setBrush(pal.color(QPalette::Light));
        painter.drawRect(rect);

        // Setup color
        // Used for navigation solution?
        if( satInfo.bUsedForNav == true) {
            // GPS
            if( satInfo.nConstType == CT_GPS ) {
                painter.setBrush(QColor(0, 0, 128));
            }
            // GLONASS
            else if( satInfo.nConstType == CT_GLONASS ){
                painter.setBrush(QColor(128, 0, 0));
            }
            // Check for GNSS - here we have GPS and GLONASS
            else if( satInfo.nConstType == CT_GNSS ){
                // GPS
                if( satInfo.nPRN >= NP_GPS_MIN_PRN && satInfo.nPRN <= NP_WAAS_MAX_PRN) {
                    painter.setBrush(QColor(0, 0, 128));
                }
                // GLONASS
                else if( satInfo.nPRN >= NP_GLONASS_MIN_PRN && satInfo.nPRN <= NP_GLONASS_MAX_PRN){
                    painter.setBrush(QColor(128, 0, 0));
                }
            }
            // GALILEO
            else if( satInfo.nConstType == CT_GALILEO ){
                painter.setBrush(QColor(128, 128, 0));
            }
        }
        // Not used for the navigation solution
        else {
            // GALILEO
            if( satInfo.nConstType == CT_GALILEO ){
                painter.setBrush(QColor(128, 0, 128));
            }
            // Everything else
            else {
                if( (satInfo.nConstType == CT_GPS) && (satInfo.nPRN >= NP_WAAS_MIN_PRN && satInfo.nPRN <= NP_WAAS_MAX_PRN) ) {
                    painter.setBrush(QColor(0, 128, 0));
                }
                else if( satInfo.nPRN >= NP_GPS_MIN_PRN && satInfo.nPRN <= NP_WAAS_MAX_PRN) {
                    painter.setBrush(QColor(64, 64, 64));
                }
                else if( satInfo.nPRN >= NP_GLONASS_MIN_PRN && satInfo.nPRN <= NP_GLONASS_MAX_PRN){
                    painter.setBrush(QColor(64, 64, 64));
                }
                else {
                    painter.setBrush(QColor(64, 64, 64));
                }
            }
        }

        //
        // Draw actual signal strength
        //
        qreal dRatio = static_cast<qreal>(rect.height()) / 50.0;
        QRectF rcSignal = rect;
        qreal dSigQual = static_cast<qreal>(satInfo.nSNR);

        qreal dHeight = dSigQual * dRatio;
        rcSignal.setHeight(dHeight);
        rcSignal.moveTop(rect.bottom() - dHeight);

        painter.drawRect(rcSignal);

        //
        // Draw text
        //
        // First the signal strength
        //
        painter.setPen(pal.color(QPalette::HighlightedText));
        QString str = QString("%1").arg(dSigQual);
        painter.drawText(rcSignal, str, Qt::AlignTop | Qt::AlignHCenter);
        //
        // Now draw the PRN
        //
        QRect rcPRNText(
                    static_cast<int>(rcSignal.left()),
                    static_cast<int>(rect.bottom()),
                    static_cast<int>(rcSignal.width()),
                    static_cast<int>(dPRNTextBoxHeight));
        painter.setPen(pal.color(QPalette::BrightText));
        str = QString("%1").arg(satInfo.nPRN);
        painter.drawText(rcPRNText, str, Qt::AlignVCenter | Qt::AlignHCenter);

        //
        // Move to next channel
        //
        x += dWidth;
        rect.moveTo(x, 0.0);
    }
}

QSize CSignalQuality::sizeHint () const{
    return QSize(200, 200);
}

