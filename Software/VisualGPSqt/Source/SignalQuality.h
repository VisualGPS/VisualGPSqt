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
#ifndef SIGNALQUALITY_H
#define SIGNALQUALITY_H

#include <QWidget>
#include <string>
#include "NMEAParserQt.h"

class CSignalQuality : public QWidget
{
    Q_OBJECT

private:

    ///
    /// \brief The CONSTALLATION_TYPE_E enum Supported GNSS constellations
    ///
    enum CONSTALLATION_TYPE_E {
        CT_UNKNOWN = 0,                                     ///< Thie wild west
        CT_GPS,                                             ///< GPS (US)
        CT_GLONASS,                                         ///< GLONASS (Russia)
        CT_GNSS,                                            ///< GNSS (mixed - US/RUSSIA - but can differ)
        CT_GALILEO,                                         ///< Galileo (EU)
        CT_BEIDOU,                                          ///< Beidou constellation
    };

    typedef struct _SAT_INFO_T {
        int                     nPRN;                       ///< Satellite pseudo random number (ID)
        int                     nSNR;                       ///< Signal to noise ratio
        bool                    bUsedForNav;                ///< Used in nav/timing solution
        CONSTALLATION_TYPE_E    nConstType;                 ///< Constellation type
        std::string             strNmeaSpec;                ///< Part of the NMEA Specification
    } SAT_INFO_T;                                           ///< Satellite information for all GPS constellations

    const static int            c_nMaxChannels = 256;       ///< Max number of channels this class can handle
    CNMEAParserQt *             m_pNMEAParser;              ///< The main NMEA parser

public:
    explicit CSignalQuality(CNMEAParserQt *pNMEAParser, QWidget *parent = nullptr);

signals:

public slots:
    void OnNewPositionUpdateGPS();
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    ///
    /// \brief ConsolidateSatData Here we will combine all of the different GNSS constellations
    /// into one big constellation which will be stored in mapSatData.
    ///
    /// \param mapSatData
    ///
    void ConsolidateSatData(std::map<std::string, SAT_INFO_T> &mapSatData);

    ///
    /// \brief Draws the GPS signal quality
    ///
    void DrawScreen();
};

#endif // SIGNALQUALITY_H
