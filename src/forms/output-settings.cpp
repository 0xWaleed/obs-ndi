/*
obs-ndi
Copyright (C) 2016-2018 St�phane Lepin <steph  name of author

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; If not, see <https://www.gnu.org/licenses/>
*/

#include "output-settings.h"
#include "ui_output-settings.h"

#include "../Config.h"
#include "../obs-ndi.h"

OutputSettings::OutputSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OutputSettings) {
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()),
        this, SLOT(onFormAccepted()));
}

void OutputSettings::onFormAccepted() {
    Config* conf = Config::Current();
    conf->OutputEnabled = ui->outputEnabled->isChecked();
    conf->OutputName = ui->outputName->text();
    conf->OutputAsyncEnabled = ui->asyncSendingEnabled->isChecked();
    conf->Save();

    if (conf->OutputEnabled) {
        if (main_output_is_running()) {
            main_output_stop();
        }
        main_output_start(ui->outputName->text().toUtf8().constData());
    } else {
        main_output_stop();
    }
}

void OutputSettings::showEvent(QShowEvent* event) {
    Config* conf = Config::Current();
    ui->outputEnabled->setChecked(conf->OutputEnabled);
    ui->outputName->setText(conf->OutputName);
    ui->asyncSendingEnabled->setChecked(conf->OutputAsyncEnabled);
}

void OutputSettings::ToggleShowHide() {
    if (!isVisible())
        setVisible(true);
    else
        setVisible(false);
}

OutputSettings::~OutputSettings() {
    delete ui;
}
