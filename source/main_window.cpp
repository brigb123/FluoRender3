/**
 * Copyright (c) 2009, Paul Gideon Dann
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include "main_window.h"
#include "moc_main_window.cpp"
#include <QColorDialog>
#include <sstream>
#include <cstdio>
#include <iostream>

/**
 * Constructor
 */
MainWindow::MainWindow(QMainWindow* parent)
: QMainWindow(parent)
{
  this->ui.setupUi(this);
}
void MainWindow::setPropColorText() {
  std::string ss(this->ui.colorPropText->text().toStdString());
  int r,g,b;
  if (3 != sscanf(ss.c_str(),"%d, %d, %d",&r,&g,&b)) return;
  r = std::min(std::max(r,0),255);
  g = std::min(std::max(g,0),255);
  b = std::min(std::max(b,0),255);
  QString qss = QString("background-color: rgb(%1,%2,%3);").arg(r).arg(g).arg(b);
    this->ui.colorPropButton->setStyleSheet(qss);
}

void MainWindow::setPropColor() {
  QColor c = QColorDialog::getColor(
      this->ui.colorPropButton->palette().color(QPalette::Window));
  QString qss = QString("background-color: %1").arg(c.name());
  this->ui.colorPropButton->setStyleSheet(qss);
  QString txt = QString("%1, %2, %3").arg(c.red()).arg(c.green()).arg(c.blue());
  this->ui.colorPropText->setText(txt);
}

void MainWindow::keyPressEvent(QKeyEvent *k) {
  switch(k->key()) {
  case Qt::Key_Shift:
    this->ui.highlightButton->setChecked(true);
    break;
  case Qt::Key_Z:
    this->ui.diffuseHighlightButton->setChecked(true);
    break;
  case Qt::Key_X:
    this->ui.resetHighlightedButton->setChecked(true);
    break;
  default:
    QMainWindow::keyPressEvent(k);
    break;
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *k) {
  switch(k->key()) {
  case Qt::Key_Shift:
    this->ui.highlightButton->setChecked(false);
    break;
  case Qt::Key_Z:
    this->ui.diffuseHighlightButton->setChecked(false);
    break;
  case Qt::Key_X:
    this->ui.resetHighlightedButton->setChecked(false);
    break;
  default:
    QMainWindow::keyPressEvent(k);
    break;
  }
}
