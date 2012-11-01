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

#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include "enums.h"

#include <QtCore/QString>
#include <QtGui/QPixmap>
#include <QtGui/QImageReader>

//! Image loader class
class ImageLoader: public QObject
{
    Q_OBJECT

public:
    ImageLoader(QObject *parent = 0);
    ~ImageLoader();

    void setSource(const QString &source);
    QString source() const;

    void setPercentLoading(const qreal &percent);
    qreal percentLoading() const;

    QPixmap generatePartialPixmap(const QPoint &startPoint, const QSize &size);
    //void generateFirstImage(const QPoint &pos = QPoint(0, 0));// TODO maybe this function will be another one

protected:
    QImageReader m_imageReader;
    qreal m_percentLoading;

    QString m_source;
    int m_imageWidth;
    int m_imageHeight;
};

#endif /* _IMAGELOADER */
