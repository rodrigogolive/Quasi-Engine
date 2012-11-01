/**
 * Copyright (C) 2012 by INdT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * @author Rodrigo Goncalves de Oliveira <rodrigo.goncalves@openbossa.org>
 * @author Roger Felipe Zanoni da Silva <roger.zanoni@openbossa.org>
 */

#include "imageloader.h"

//! Class constructor
ImageLoader::ImageLoader(QObject *parent)
    : QObject(parent)
    , m_percentLoading(0.1)
{
}

//! Class destructor
ImageLoader::~ImageLoader()
{
}

//! Stores the source path for the image
/*!
 * \param source the image path
 */
void ImageLoader::setSource(const QString &source)
{
    if (m_source == source) {
        m_source = source;

        m_imageReader.setFileName(m_source);
        m_imageWidth = m_imageReader.size().width();
        m_imageHeight = m_imageReader.size().height();
    }
}

//! Gets the image source path
/*!
 * \return the source path for the image
 */
QString ImageLoader::source() const
{
    return m_source;
}

void ImageLoader::setPercentLoading(const qreal &percent)
{
    if (m_percentLoading != percent)
        m_percentLoading = qBound(0.0, percent, 1.0);
}

qreal ImageLoader::percentLoading() const
{
    return m_percentLoading;
}

/*void ImageLoader::generateFirstImage(const QPoint &pos)
{
    // XXX this function needs improvements
    if (!m_imageReader.canRead())
        m_imageReader.setFileName(m_source); // XXX me doesn't like this

    int readerWidth = m_imageReader.size().width();
    int readerHeight = m_imageReader.size().height();

    int hDelta = boundingRect().width() * m_percentLoading;
    int vDelta = boundingRect().height() * m_percentLoading;

    // if want to use the same governor
    //if (hDelta > vDelta)
    //    vDelta = hDelta;
    //else
    //    hDelta = vDelta;

    // for viewport
    int realX = pos.x(); // 10546
    int realY = pos.y(); // 800
    int realW = boundingRect().width();
    int realH = boundingRect().height();
    // for extra border
    int newX = realX - hDelta;
    int newY = realY - vDelta;
    int newW = realW + (2 * hDelta);
    int newH = realH + (2 * vDelta);

    bool bigW = false;
    bool bigH = false;
    if (newX + newW > readerWidth) {
        newW = readerWidth - newX;
        bigW = true;
    }
    if (newY + newH > readerHeight) {
        bigH = true;
        newH = readerHeight - newY;
    }
    // if infinite
    //if (realX <= 0)
    //    newX = 0;
    //if (realY <= 0)
    //    newY = 0;

    m_imageReader.setClipRect(QRect(newX, newY, newW, newH));

    QPixmap pix(realW + (2 * hDelta), realH + (2 * vDelta));
    QPainter p(&pix);
        //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/CUEN.png");///
        p.drawPixmap(0, 0, QPixmap::fromImageReader(&m_imageReader));

        if (newX < 0 && newY < 0) { // XXX free-for-all
            qDebug() << "CUEN1";
            // top-left
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(readerWidth + newX, readerHeight + newY, hDelta, vDelta));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen1.png");///
            p.drawPixmap(0, 0, QPixmap::fromImageReader(&m_imageReader));

            // top-right
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(0, readerHeight + newY, newW, vDelta));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen2.png");///
            p.drawPixmap(-newX, 0, QPixmap::fromImageReader(&m_imageReader));

            // bottom-left
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(readerWidth + newX, 0, hDelta, newH));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen3.png");///
            p.drawPixmap(0, -newY, QPixmap::fromImageReader(&m_imageReader));
        } else if (newX < 0 && newY >= 0 && !bigH) { // XXX fixed H
            qDebug() << "CUEN2";
            // left
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(readerWidth + newX, newY, -newX, newH));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen3.png");///
            p.drawPixmap(0, 0, QPixmap::fromImageReader(&m_imageReader));
        } else if (newY < 0 && newX >= 0 && !bigW) { // XXX fixed V
            qDebug() << "CUEN3";
            // top
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(newX, readerHeight + newY, newW, -newY));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen2.png");///
            p.drawPixmap(0, 0, QPixmap::fromImageReader(&m_imageReader));
        } else if (bigW && bigH) { // free-for-all
            qDebug() << "CUEN4";
            // bottom-right
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(0, 0, realW + (2 * hDelta) - newW, realH + (2 * vDelta) - newH));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen1.png");///
            p.drawPixmap(newW, newH, QPixmap::fromImageReader(&m_imageReader));

            // top-right
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(0, newY, realW + (2 * hDelta) - newW, readerHeight - newY));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen2.png");///
            p.drawPixmap(readerWidth - newX, 0, QPixmap::fromImageReader(&m_imageReader));

            // bottom-left
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(newX, 0, readerWidth - newX, realH + (2 * vDelta) - newH));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen3.png");///
            p.drawPixmap(0, readerHeight - newY, QPixmap::fromImageReader(&m_imageReader));
        } else if (bigW && !bigH && newY >= 0) { // free-for-all
            qDebug() << "CUEN5";
            // right
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(0, newY, realW + (2 * hDelta) - newW, newH));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen2.png");///
            p.drawPixmap(readerWidth - newX, 0, QPixmap::fromImageReader(&m_imageReader));
        } else if (!bigW && bigH && newX < 0) { // free-for-all
            qDebug() << "CUEN6";
            // top-left
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(readerWidth + newX, newY, hDelta, vDelta));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen1.png");///
            p.drawPixmap(0, 0, QPixmap::fromImageReader(&m_imageReader));

            // bottom-left
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(readerWidth + newX, 0, hDelta, realH + (2 * vDelta) - newH));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen3.png");///
            p.drawPixmap(0, newH, QPixmap::fromImageReader(&m_imageReader));

            // bottom-right
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(0, 0, newW - hDelta, realH + (2 * vDelta) - newH));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen2.png");///
            p.drawPixmap(-newX, newH, QPixmap::fromImageReader(&m_imageReader));
        } else if (!bigW && bigH) { // free-for-all
            qDebug() << "CUEN7";
            // bottom
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(newX, 0, newW, realH + (2 * vDelta) - newH));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen2.png");///
            p.drawPixmap(0, newH, QPixmap::fromImageReader(&m_imageReader));
        } else if (bigW && !bigH && newY < 0) { // free-for-all
            qDebug() << "CUEN8";
            // top-left
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(newX, readerHeight + newY, newW, vDelta));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen1.png");///
            p.drawPixmap(0, 0, QPixmap::fromImageReader(&m_imageReader));

            // top-right
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(0, readerHeight + newY, realW + (2 * hDelta) - newW, vDelta));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen2.png");///
            p.drawPixmap(readerWidth - newX, 0, QPixmap::fromImageReader(&m_imageReader));

            // bottom-right
            m_imageReader.setFileName(m_source);
            m_imageReader.setClipRect(QRect(0, 0, realW + (2 * hDelta) - newW, newH - vDelta));
            //QPixmap::fromImageReader(&m_imageReader).save("/tmp/ABC/cuen2.png");///
            p.drawPixmap(readerWidth - newX, -newY, QPixmap::fromImageReader(&m_imageReader));
        }

        QColor c(Qt::red);
        c.setAlphaF(0.5);
        p.fillRect(hDelta, vDelta, realW, realH, c);///
    p.end();

}*/
///

QPixmap ImageLoader::load(const QPoint &startPoint, const QSize &size)
{
    if (!m_imageReader.canRead())
        m_imageReader.setFileName(m_source); // XXX me doesn't like this

    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    if (m_type == 0) { // hFixed
        width = size.width() * m_percentLoading;
        x = startPoint.x() - (startPoint.x() * m_percentLoading);
    } else if (m_type == 1) { // vFixed
        height = size.height() * m_percentLoading;
        y = startPoint.y() - (startPoint.y() * m_percentLoading);
    } else { // freedom \o/
        width = size.width() * m_percentLoading;
        height = size.height() * m_percentLoading;
        x = startPoint.x() - (startPoint.x() * m_percentLoading);
        y = startPoint.y() - (startPoint.y() * m_percentLoading);
    }

    m_imageReader.setClipRect(QRect(x, y, width, height));
    //m_imageReader.setClipRect(QRect(startPoint,
    //                            0,
    //                            size,
    //                            boundingRect().height() * 1));

    return QPixmap::fromImageReader(&m_imageReader);
}
