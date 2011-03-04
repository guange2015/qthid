/***************************************************************************
 *  This file is part of Qthid.
 * 
 *  Copyright (C) 2010  Howard Long, G6LVB
 * 
 *  Qthid is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Qthid is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Qthid.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***************************************************************************/

#include <QtGui>
#include <QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hidapi.h"
#include "fcd.h"
#include "fcdhidcmd.h"


static const COMBOITEMSTRUCT _cisLNAGain[]=
{
    {QT_TR_NOOP("-5.0dB"),TLGE_N5_0DB},
    {QT_TR_NOOP("-2.5dB"),TLGE_N2_5DB},
    {QT_TR_NOOP("+0.0dB"),TLGE_P0_0DB},
    {QT_TR_NOOP("+2.5dB"),TLGE_P2_5DB},
    {QT_TR_NOOP("+5,0dB"),TLGE_P5_0DB},
    {QT_TR_NOOP("+7.5dB"),TLGE_P7_5DB},
    {QT_TR_NOOP("+10.0dB"),TLGE_P10_0DB},
    {QT_TR_NOOP("+12.5dB"),TLGE_P12_5DB},
    {QT_TR_NOOP("+15.0dB"),TLGE_P15_0DB},
    {QT_TR_NOOP("+17.5dB"),TLGE_P17_5DB},
    {QT_TR_NOOP("+20.0dB"),TLGE_P20_0DB},
    {QT_TR_NOOP("+25.0dB"),TLGE_P25_0DB},
    {QT_TR_NOOP("+30.0dB"),TLGE_P30_0DB},
    {NULL,0}
};
static const COMBOITEMSTRUCT _cisLNAEnhance[]=
{
        {QT_TR_NOOP("Off"),TLEE_OFF},
        {QT_TR_NOOP("0"),TLEE_0},
        {QT_TR_NOOP("1"),TLEE_1},
        {QT_TR_NOOP("2"),TLEE_2},
        {QT_TR_NOOP("3"),TLEE_3},
        {NULL,0}
};

static const COMBOITEMSTRUCT _cisBand[]=
{
        {QT_TR_NOOP("VHF II"),TBE_VHF2},
        {QT_TR_NOOP("VHF III"),TBE_VHF3},
        {QT_TR_NOOP("UHF"),TBE_UHF},
        {QT_TR_NOOP("L band"),TBE_LBAND},
        {NULL,0}
};
static const COMBOITEMSTRUCT _cisRFFilter0[]=
{
        {QT_TR_NOOP("268MHz LPF"),TRFE_LPF268MHZ},
        {QT_TR_NOOP("299MHz LPF"),TRFE_LPF268MHZ},
        {NULL,0}
};

static const COMBOITEMSTRUCT _cisRFFilter1[]=
{
        {QT_TR_NOOP("509MHz LPF"),TRFE_LPF509MHZ},
        {QT_TR_NOOP("656MHz LPF"),TRFE_LPF656MHZ},
        {NULL,0}
};
static const COMBOITEMSTRUCT _cisRFFilter2[]=
{
        {QT_TR_NOOP("360MHz BPF"),TRFE_BPF360MHZ},
        {QT_TR_NOOP("380MHz BPF"),TRFE_BPF380MHZ},
        {QT_TR_NOOP("405MHz BPF"),TRFE_BPF405MHZ},
        {QT_TR_NOOP("425MHz BPF"),TRFE_BPF425MHZ},
        {QT_TR_NOOP("450MHz BPF"),TRFE_BPF450MHZ},
        {QT_TR_NOOP("475MHz BPF"),TRFE_BPF475MHZ},
        {QT_TR_NOOP("505MHz BPF"),TRFE_BPF505MHZ},
        {QT_TR_NOOP("540MHz BPF"),TRFE_BPF540MHZ},
        {QT_TR_NOOP("575MHz BPF"),TRFE_BPF575MHZ},
        {QT_TR_NOOP("615MHz BPF"),TRFE_BPF615MHZ},
        {QT_TR_NOOP("670MHz BPF"),TRFE_BPF670MHZ},
        {QT_TR_NOOP("720MHz BPF"),TRFE_BPF720MHZ},
        {QT_TR_NOOP("760MHz BPF"),TRFE_BPF760MHZ},
        {QT_TR_NOOP("840MHz BPF"),TRFE_BPF840MHZ},
        {QT_TR_NOOP("890MHz BPF"),TRFE_BPF890MHZ},
        {QT_TR_NOOP("970MHz BPF"),TRFE_BPF970MHZ},
        {NULL,0}
};static const COMBOITEMSTRUCT _cisRFFilter3[]=
{
        {QT_TR_NOOP("1300MHz BPF"),TRFE_BPF1300MHZ},
        {QT_TR_NOOP("1320MHz BPF"),TRFE_BPF1320MHZ},
        {QT_TR_NOOP("1360MHz BPF"),TRFE_BPF1360MHZ},
        {QT_TR_NOOP("1410MHz BPF"),TRFE_BPF1410MHZ},
        {QT_TR_NOOP("1445MHz BPF"),TRFE_BPF1445MHZ},
        {QT_TR_NOOP("1460MHz BPF"),TRFE_BPF1460MHZ},
        {QT_TR_NOOP("1490MHz BPF"),TRFE_BPF1490MHZ},
        {QT_TR_NOOP("1530MHz BPF"),TRFE_BPF1530MHZ},
        {QT_TR_NOOP("1560MHz BPF"),TRFE_BPF1560MHZ},
        {QT_TR_NOOP("1590MHz BPF"),TRFE_BPF1590MHZ},
        {QT_TR_NOOP("1640MHz BPF"),TRFE_BPF1640MHZ},
        {QT_TR_NOOP("1660MHz BPF"),TRFE_BPF1660MHZ},
        {QT_TR_NOOP("1680MHz BPF"),TRFE_BPF1680MHZ},
        {QT_TR_NOOP("1700MHz BPF"),TRFE_BPF1700MHZ},
        {QT_TR_NOOP("1720MHz BPF"),TRFE_BPF1720MHZ},
        {QT_TR_NOOP("1750MHz BPF"),TRFE_BPF1750MHZ},
        {NULL,0}
};

static const COMBOITEMSTRUCT _cisMixerGain[]=
{
        {QT_TR_NOOP("4dB"),TMGE_P4_0DB},
        {QT_TR_NOOP("12dB"),TMGE_P12_0DB},
        {NULL,0}
};
static const COMBOITEMSTRUCT _cisBiasCurrent[]=
{
        {QT_TR_NOOP("00 L band"),TBCE_LBAND},
        {QT_TR_NOOP("01"),TBCE_1},
        {QT_TR_NOOP("10"),TBCE_2},
        {QT_TR_NOOP("11 V/U band"),TBCE_VUBAND},
        {NULL,0}
};

static const COMBOITEMSTRUCT _cisMixerFilter[]=
{
        {QT_TR_NOOP("1.9MHz"),TMFE_1_9MHZ},
        {QT_TR_NOOP("2.3MHz"),TMFE_2_3MHZ},
        {QT_TR_NOOP("2.7MHz"),TMFE_2_7MHZ},
        {QT_TR_NOOP("3.0MHz"),TMFE_3_0MHZ},
        {QT_TR_NOOP("3.4MHz"),TMFE_3_4MHZ},
        {QT_TR_NOOP("3.8MHz"),TMFE_3_8MHZ},
        {QT_TR_NOOP("4.2MHz"),TMFE_4_2MHZ},
        {QT_TR_NOOP("4.6MHz"),TMFE_4_6MHZ},
        {QT_TR_NOOP("27MHz"),TMFE_27_0MHZ},
        {NULL,0}
};
static const COMBOITEMSTRUCT _cisIFGain1[]=
{
        {QT_TR_NOOP("-3dB"),TIG1E_N3_0DB},
        {QT_TR_NOOP("+6dB"),TIG1E_P6_0DB},
        {NULL,0}
};

static const COMBOITEMSTRUCT _cisIFGainMode[]=
{
        {QT_TR_NOOP("Linearity"),TIGME_LINEARITY},
        {QT_TR_NOOP("Sensitivity"),TIGME_SENSITIVITY},
        {NULL,0}
};
static const COMBOITEMSTRUCT _cisIFRCFilter[]=
{
        {QT_TR_NOOP("1.0MHz"),TIRFE_1_0MHZ},
        {QT_TR_NOOP("1.2MHz"),TIRFE_1_2MHZ},
        {QT_TR_NOOP("1.8MHz"),TIRFE_1_8MHZ},
        {QT_TR_NOOP("2.6MHz"),TIRFE_2_6MHZ},
        {QT_TR_NOOP("3.4MHz"),TIRFE_3_4MHZ},
        {QT_TR_NOOP("4.4MHz"),TIRFE_4_4MHZ},
        {QT_TR_NOOP("5.3MHz"),TIRFE_5_3MHZ},
        {QT_TR_NOOP("6.4MHz"),TIRFE_6_4MHZ},
        {QT_TR_NOOP("7.7MHz"),TIRFE_7_7MHZ},
        {QT_TR_NOOP("9.0MHz"),TIRFE_9_0MHZ},
        {QT_TR_NOOP("10.6MHz"),TIRFE_10_6MHZ},
        {QT_TR_NOOP("12.4MHz"),TIRFE_12_4MHZ},
        {QT_TR_NOOP("14.7MHz"),TIRFE_14_7MHZ},
        {QT_TR_NOOP("17.6MHz"),TIRFE_17_6MHZ},
        {QT_TR_NOOP("21.0MHz"),TIRFE_21_0MHZ},
        {QT_TR_NOOP("21.4MHz"),TIRFE_21_4MHZ},
        {NULL,0}
};
static const COMBOITEMSTRUCT _cisIFGain2[]=
{
        {QT_TR_NOOP("0dB"),TIG2E_P0_0DB},
        {QT_TR_NOOP("+3dB"),TIG2E_P3_0DB},
        {QT_TR_NOOP("+6dB"),TIG2E_P6_0DB},
        {QT_TR_NOOP("+9dB"),TIG2E_P9_0DB},
        {NULL,0}
};

static const COMBOITEMSTRUCT _cisIFGain3[]=
{
        {QT_TR_NOOP("0dB"),TIG3E_P0_0DB},
        {QT_TR_NOOP("+3dB"),TIG3E_P3_0DB},
        {QT_TR_NOOP("+6dB"),TIG3E_P6_0DB},
        {QT_TR_NOOP("+9dB"),TIG3E_P9_0DB},
        {NULL,0}
};

static const COMBOITEMSTRUCT _cisIFGain4[]=
{
        {QT_TR_NOOP("0dB"),TIG4E_P0_0DB},
        {QT_TR_NOOP("+1dB"),TIG4E_P1_0DB},
        {QT_TR_NOOP("+2dB"),TIG4E_P2_0DB},
        {NULL,0}
};static const COMBOITEMSTRUCT _cisIFFilter[]=
{
        {QT_TR_NOOP("2.15MHz"),TIFE_2_15MHZ},
        {QT_TR_NOOP("2.20MHz"),TIFE_2_20MHZ},
        {QT_TR_NOOP("2.24MHz"),TIFE_2_24MHZ},
        {QT_TR_NOOP("2.28MHz"),TIFE_2_28MHZ},
        {QT_TR_NOOP("2.30MHz"),TIFE_2_30MHZ},
        {QT_TR_NOOP("2.40MHz"),TIFE_2_40MHZ},
        {QT_TR_NOOP("2.45MHz"),TIFE_2_45MHZ},
        {QT_TR_NOOP("2.50MHz"),TIFE_2_50MHZ},
        {QT_TR_NOOP("2.55MHz"),TIFE_2_55MHZ},
        {QT_TR_NOOP("2.60MHz"),TIFE_2_60MHZ},
        {QT_TR_NOOP("2.70MHz"),TIFE_2_70MHZ},
        {QT_TR_NOOP("2.75MHz"),TIFE_2_75MHZ},
        {QT_TR_NOOP("2.80MHz"),TIFE_2_80MHZ},
        {QT_TR_NOOP("2.90MHz"),TIFE_2_90MHZ},
        {QT_TR_NOOP("2.95MHz"),TIFE_2_95MHZ},
        {QT_TR_NOOP("3.00MHz"),TIFE_3_00MHZ},
        {QT_TR_NOOP("3.10MHz"),TIFE_3_10MHZ},
        {QT_TR_NOOP("3.20MHz"),TIFE_3_20MHZ},
        {QT_TR_NOOP("3.30MHz"),TIFE_3_30MHZ},
        {QT_TR_NOOP("3.40MHz"),TIFE_3_40MHZ},
        {QT_TR_NOOP("3.60MHz"),TIFE_3_60MHZ},
        {QT_TR_NOOP("3.70MHz"),TIFE_3_70MHZ},
        {QT_TR_NOOP("3.80MHz"),TIFE_3_80MHZ},
        {QT_TR_NOOP("3.90MHz"),TIFE_3_90MHZ},
        {QT_TR_NOOP("4.10MHz"),TIFE_4_10MHZ},
        {QT_TR_NOOP("4.30MHz"),TIFE_4_30MHZ},
        {QT_TR_NOOP("4.40MHz"),TIFE_4_40MHZ},
        {QT_TR_NOOP("4.60MHz"),TIFE_4_60MHZ},
        {QT_TR_NOOP("4.80MHz"),TIFE_4_80MHZ},
        {QT_TR_NOOP("5.00MHz"),TIFE_5_00MHZ},
        {QT_TR_NOOP("5.30MHz"),TIFE_5_30MHZ},
        {QT_TR_NOOP("5.50MHz"),TIFE_5_50MHZ},
        {NULL,0}
};static const COMBOITEMSTRUCT _cisIFGain5[]=
{
        {QT_TR_NOOP("+3dB"),TIG5E_P3_0DB},
        {QT_TR_NOOP("+6dB"),TIG5E_P6_0DB},
        {QT_TR_NOOP("+9dB"),TIG5E_P9_0DB},
        {QT_TR_NOOP("+12dB"),TIG5E_P12_0DB},
        {QT_TR_NOOP("+15dB"),TIG5E_P15_0DB},
        {NULL,0}
};

static const COMBOITEMSTRUCT _cisIFGain6[]=
{
        {QT_TR_NOOP("+3dB"),TIG6E_P3_0DB},
        {QT_TR_NOOP("+6dB"),TIG6E_P6_0DB},
        {QT_TR_NOOP("+9dB"),TIG6E_P9_0DB},
        {QT_TR_NOOP("+12dB"),TIG6E_P12_0DB},
        {QT_TR_NOOP("+15dB"),TIG6E_P15_0DB},
        {NULL,0}
};

static COMBOSTRUCT _acs[]=
{
    {FCD_HID_CMD_SET_LNA_GAIN,    FCD_HID_CMD_GET_LNA_GAIN,    10, NULL, _cisLNAGain},
    {FCD_HID_CMD_SET_LNA_ENHANCE, FCD_HID_CMD_GET_LNA_ENHANCE,  0, NULL, _cisLNAEnhance},
    {FCD_HID_CMD_SET_BAND,        FCD_HID_CMD_GET_BAND,         0, NULL, _cisBand},
    {FCD_HID_CMD_SET_RF_FILTER,   FCD_HID_CMD_GET_RF_FILTER,    0, NULL, _cisRFFilter1},
    { FCD_HID_CMD_SET_MIXER_GAIN,  FCD_HID_CMD_GET_MIXER_GAIN,   1, NULL, _cisMixerGain},
    {FCD_HID_CMD_SET_BIAS_CURRENT,FCD_HID_CMD_GET_BIAS_CURRENT, 3, NULL, _cisBiasCurrent},
    {FCD_HID_CMD_SET_MIXER_FILTER,FCD_HID_CMD_GET_MIXER_FILTER, 0, NULL, _cisMixerFilter},
    {FCD_HID_CMD_SET_IF_GAIN1,    FCD_HID_CMD_GET_IF_GAIN1,     1, NULL, _cisIFGain1},
    {FCD_HID_CMD_SET_IF_GAIN_MODE,FCD_HID_CMD_GET_IF_GAIN_MODE, 0, NULL, _cisIFGainMode},
    {FCD_HID_CMD_SET_IF_RC_FILTER,FCD_HID_CMD_GET_IF_RC_FILTER, 0, NULL, _cisIFRCFilter},
    {FCD_HID_CMD_SET_IF_GAIN2,    FCD_HID_CMD_GET_IF_GAIN2,     0, NULL, _cisIFGain2},
    {FCD_HID_CMD_SET_IF_GAIN3,    FCD_HID_CMD_GET_IF_GAIN3,     0, NULL, _cisIFGain3},
    {FCD_HID_CMD_SET_IF_GAIN4,    FCD_HID_CMD_GET_IF_GAIN4,     0, NULL, _cisIFGain4},
    {FCD_HID_CMD_SET_IF_FILTER,   FCD_HID_CMD_GET_IF_FILTER,    0, NULL, _cisIFFilter},
    {FCD_HID_CMD_SET_IF_GAIN5,    FCD_HID_CMD_GET_IF_GAIN5,     0, NULL, _cisIFGain5},
    {FCD_HID_CMD_SET_IF_GAIN6,    FCD_HID_CMD_GET_IF_GAIN6,     0, NULL, _cisIFGain6},
    {0,0,0,NULL, NULL}
};



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSettings settings;

    ui->setupUi(this);

    ui->lineEditFreq->setText(settings.value("Frequency","97,300.000").toString());
    ui->lineEditStep->setText(settings.value("Step","25,000").toString());
    ui->spinBoxCorr->setValue(settings.value("Correction","-120").toInt());

    ui->doubleSpinBoxDCI->setValue(settings.value("DCICorr","0.0").toDouble());
    ui->doubleSpinBoxDCQ->setValue(settings.value("DCQCorr","0.0").toDouble());
    ui->doubleSpinBoxPhase->setValue(settings.value("PhaseCorr","0.0").toDouble());
    ui->doubleSpinBoxGain->setValue(settings.value("GaunCorr","0.0").toDouble());


    /* Populate Combo Box list structure - unlike windows API, we dont have fixed ids... */
    _acs[0].pComboBox=ui->comboBoxLNAGain;
    _acs[1].pComboBox=ui->comboBoxLNAEnhance;
    _acs[2].pComboBox=ui->comboBoxBand;
    _acs[3].pComboBox=ui->comboBoxRfFilter;
    _acs[4].pComboBox=ui->comboBoxMixerGain;
    _acs[5].pComboBox=ui->comboBoxBiasCurrent;
    _acs[6].pComboBox=ui->comboBoxMixerFilter;
    _acs[7].pComboBox=ui->comboBoxIFGain1;
    _acs[8].pComboBox=ui->comboBoxIFGainMode;
    _acs[9].pComboBox=ui->comboBoxIFRCFilter;
    _acs[10].pComboBox=ui->comboBoxIFGain2;
    _acs[11].pComboBox=ui->comboBoxIFGain3;
    _acs[12].pComboBox=ui->comboBoxIFGain4;
    _acs[13].pComboBox=ui->comboBoxIFFilter;
    _acs[14].pComboBox=ui->comboBoxIFGain5;
    _acs[15].pComboBox=ui->comboBoxIFGain6;

    PopulateCombos();

    ReadDevice();

    EnableControls();


    setUnifiedTitleAndToolBarOnMac(true);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(EnableControls()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    QSettings settings;

    timer->stop();
    delete timer;

    settings.setValue("Frequency",ui->lineEditFreq->text());
    settings.setValue("Step",ui->lineEditStep->text());
    settings.setValue("Correction",ui->spinBoxCorr->value());
    settings.setValue("DCICorr",ui->doubleSpinBoxDCI->value());
    settings.setValue("DCQCorr",ui->doubleSpinBoxDCQ->value());
    settings.setValue("PhaseCorr",ui->doubleSpinBoxPhase->value());
    settings.setValue("GainCorr",ui->doubleSpinBoxGain->value());

    delete ui;
}
/**
 * Populates a combo box with all its items, and sets default index
 */
void MainWindow::PopulateCombo(QComboBox *box, int nIdxDefault, const COMBOITEMSTRUCT *pcis)
{
    box->clear();
    while(pcis->pszDesc != NULL){
        box->addItem(QString(pcis->pszDesc));
        pcis++;
    }
    box->setCurrentIndex(nIdxDefault);
}

void MainWindow::PopulateCombos()
{
    COMBOSTRUCT *pcs = _acs;
    /* iterate trough all combo boxes */
    while(pcs->pacis!=NULL)
    {
        const COMBOITEMSTRUCT *pcis=pcs->pacis;
        PopulateCombo(pcs->pComboBox,pcs->nIdxDefault,pcis);
        pcs++;
    }
}

void MainWindow::ReadDevice()
{
    COMBOSTRUCT *pcs=_acs;

    /* iterate through all combo boxes */
    while (pcs->pacis!=NULL)
    {
        quint8 u8;
        const COMBOITEMSTRUCT *pcis=pcs->pacis;
        int nIdx=0;

        /* read FCD value for this combo box */
        fcdAppGetParam(pcs->u8CommandGet, &u8, 1);


        //Try to find the index to the register field value
        while(pcis->pszDesc!=NULL && pcis->u8Val!=u8)
        {
            nIdx++;
            pcis++;
        }
        if(pcis->pszDesc!=NULL)
        {
            pcs->pComboBox->setCurrentIndex(nIdx);
        } else
        {
            pcs->pComboBox->setCurrentIndex(0);
        }
        BandChange();
        pcs++;
    }
}
void MainWindow::BandChange()
{
    static const COMBOITEMSTRUCT *apcis[4]={_cisRFFilter0,_cisRFFilter1,_cisRFFilter2,_cisRFFilter3};
    int nIdx=ui->comboBoxBand->currentIndex();
    int nIdxOrg=ui->comboBoxRfFilter->currentIndex();
    PopulateCombo(ui->comboBoxRfFilter,nIdxOrg,apcis[nIdx]);

}



double MainWindow::StrToDouble(QString s)
{
    int i;
    QString s2="";

    for (i=0;i<s.length();i++)
    {
        QChar c=s[i];
        if (c>='0' and c<='9')
        {
            s2+=c;
        }
    }
    s2=s2.left(10);

    return s2.toDouble();
}

void MainWindow::EnableControls()
{
    FCD_MODE_ENUM fme;
    quint8 u8;

    /* clear status string */
    ui->fcdStatusLine->clear();

/*
    {
        struct hid_device_info *devs,*cur_dev;

        devs=hid_enumerate(0x04D8,0xFB56);
        cur_dev=devs;
        while (cur_dev)
        {
            ui->plainTextEdit->appendPlainText(QString::number(cur_dev->vendor_id,16));
            ui->plainTextEdit->appendPlainText(QString::number(cur_dev->product_id,16));
            ui->plainTextEdit->appendPlainText(QString::fromAscii(cur_dev->path));
            if (cur_dev->serial_number==NULL)
            {
                ui->plainTextEdit->appendPlainText("NULL");
            }
            else
            {
                ui->plainTextEdit->appendPlainText(QString::fromWCharArray(cur_dev->serial_number));
            }
            ui->plainTextEdit->appendPlainText(QString::fromWCharArray(cur_dev->manufacturer_string));
            ui->plainTextEdit->appendPlainText(QString::fromWCharArray(cur_dev->product_string));
            cur_dev=cur_dev->next;
        }
        hid_free_enumeration(devs);
    }
*/


    fme = fcdGetMode();

    switch (fme)
    {
        case FCD_MODE_APP:
            {
                QPalette p=ui->fcdStatusLine->palette();
                p.setColor(QPalette::Base, QColor(0,255,0));//green color
                ui->fcdStatusLine->setPalette(p);
            }
            ui->fcdStatusLine->setText("FCD is active");

            u8=0;
            fcdAppGetParam(FCD_HID_CMD_GET_PLL_LOCK, &u8, 1);
            ui->checkBoxPLLLock->setChecked(u8==1);

            fcdAppGetParam(FCD_HID_CMD_GET_IF_RSSI, &u8, 1);
            ui->progressBarIFRSSI->setValue(u8);

            break;

        case FCD_MODE_BL:
            {
                QPalette p=ui->fcdStatusLine->palette();
                p.setColor(QPalette::Base, QColor(255,191,0));//amber color
                ui->fcdStatusLine->setPalette(p);
            }
            ui->fcdStatusLine->setText("FCD bootloader");
            break;

        case FCD_MODE_NONE:
            {
                QPalette p=ui->fcdStatusLine->palette();
                p.setColor(QPalette::Base, QColor(255,0,0));//red color
                ui->fcdStatusLine->setPalette(p);
            }
            ui->fcdStatusLine->setText("No FCD detected");
            break;
    }

    ui->pushButtonUpdateFirmware->setEnabled(fme==FCD_MODE_BL);
    ui->pushButtonVerifyFirmware->setEnabled(fme==FCD_MODE_BL);
    ui->pushButtonBLReset->setEnabled(fme==FCD_MODE_BL);
    ui->pushButtonAppReset->setEnabled(fme==FCD_MODE_APP);
    ui->lineEditFreq->setEnabled(fme==FCD_MODE_APP);
    ui->lineEditStep->setEnabled(fme==FCD_MODE_APP);
    ui->pushButtonUp->setEnabled(fme==FCD_MODE_APP);
    ui->pushButtonDown->setEnabled(fme==FCD_MODE_APP);
    ui->spinBoxCorr->setEnabled(fme==FCD_MODE_APP);
}

void MainWindow::on_pushButtonAppReset_clicked()
{
    /* stop timeout while FCD is reconfiguring */
    timer->stop();
    fcdAppReset();
    timer->start(1000);
}

void MainWindow::on_pushButtonBLReset_clicked()
{
    /* stop timeout while FCD is reconfiguring */
    timer->stop();
    fcdBlReset();
    timer->start(1000);
}

void MainWindow::on_pushButtonUpdateFirmware_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open FCD firmware"),
                                                    QDir::currentPath(),
                                                    tr("FCD firmware files (*.bin)"));

    if (!fileName.isNull())
    {
        QFile qf(fileName);
        qint64 qn64size=qf.size();
        char *buf=new char[qn64size];

        qDebug() << fileName;

        if (buf==NULL)
        {
            QMessageBox::critical(this,
                                  tr("FCD"),
                                  tr("Unable to allocate memory for firmware image"));

            return;
        }

        if (!qf.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("FCD"), tr("Unable to open file"));
            delete buf;

            return;
        }
        else
        {
            if (qf.read(buf,qn64size)!=qn64size)
            {
                QMessageBox::critical(this, tr("FCD"), tr("Unable to read file"));
                delete buf;
                qf.close();

                return;
            }
        }

        qf.close();

        if (fcdBlErase() != FCD_MODE_BL)
        {
            QMessageBox::critical(this, tr("FCD"), tr("Flash erase failed"));
            delete buf;

            return;
        }

        if (fcdBlWriteFirmware(buf,(int64_t)qn64size) != FCD_MODE_BL)
        {
            QMessageBox::critical(this, tr("FCD"), tr("Write firmware failed"));
            delete buf;

            return;
        }

        delete buf;

        QMessageBox::information(this, tr("FCD"), tr("Firmware successfully written!"));
    }
}

void MainWindow::on_pushButtonVerifyFirmware_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open FCD firmware"),
                                                    QDir::currentPath(),
                                                    tr("FCD firmware files (*.bin)"));

    if (!fileName.isNull())
    {
        QFile qf(fileName);
        qint64 qn64size = qf.size();
        char *buf=new char[qn64size];

        qDebug() << fileName;

        if (buf==NULL)
        {
            QMessageBox::critical(this, tr("FCD"), tr("Unable to allocate memory for firmware image"));
            return;
        }

        if (!qf.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("FCD"), tr("Unable to open file"));
            delete buf;

            return;
        }
        else
        {
            if (qf.read(buf,qn64size) != qn64size)
            {
                QMessageBox::critical(this, tr("FCD"), tr("Unable to read file"));
                delete buf;
                qf.close();

                return;
            }
        }

        qf.close();

        if (fcdBlVerifyFirmware(buf,(int64_t)qn64size) != FCD_MODE_BL)
        {
            QMessageBox::critical(this, tr("FCD"), tr("Verify firmware failed"));
            delete buf;

            return;
        }

        delete buf;

        QMessageBox::information(this, tr("FCD"), tr("Firmware successfully verified!"));
    }

}


/** \brief Frequency entry text changed.
  * \param s New frequency string.
  *
  * This slot is called when new text is entered into the frequency editor. The
  * function is also called when the UP and DOWN buttons are clicked.
  */
void MainWindow::on_lineEditFreq_textChanged(QString s)
{
    double d = StrToDouble(s);
    int nCursor = ui->lineEditFreq->cursorPosition();
    QString s2 = QLocale(QLocale()).toString(d,'f',0);

    nCursor -= s.mid(0,nCursor).count(QLocale().groupSeparator());
    nCursor += s2.mid(0,nCursor).count(QLocale().groupSeparator());

    ui->lineEditFreq->setText(s2);
    ui->lineEditFreq->setCursorPosition(nCursor);
    if (d<50000000.0 || d>2100000000.0)
    {
        QPalette p = ui->lineEditFreq->palette();
        p.setColor(QPalette::Base, QColor(255,0,0));//red color
        ui->lineEditFreq->setPalette(p);
    }
    else
    {
        QPalette p = ui->lineEditFreq->palette();
        p.setColor(QPalette::Base, QColor(0,255,0));//green color
        ui->lineEditFreq->setPalette(p);
    }

    d *= 1.0 + ui->spinBoxCorr->value()/1000000.0;

    fcdAppSetFreqkHz((int)(d/1000.0));
    //ReadDevice();
}


/** \brief Frequency step entry text changed.
  * \param s New frequency step.
  *
  * This slot is called when new text is entered into the frequency step
  * editor.
  */
void MainWindow::on_lineEditStep_textChanged(QString s)
{
    double d = StrToDouble(s);
    int nCursor = ui->lineEditStep->cursorPosition();
    QString s2 = QLocale(QLocale()).toString(d,'f',0);

    nCursor -= s.mid(0,nCursor).count(QLocale().groupSeparator());
    nCursor += s2.mid(0,nCursor).count(QLocale().groupSeparator());

    ui->lineEditStep->setText(s2);
    ui->lineEditStep->setCursorPosition(nCursor);
    if (d<1.0 || d>1000000000.0)
    {
        QPalette p = ui->lineEditStep->palette();
        p.setColor(QPalette::Base, QColor(255,0,0));//red color
        ui->lineEditStep->setPalette(p);
    }
    else
    {
        QPalette p = ui->lineEditStep->palette();
        p.setColor(QPalette::Base, QColor(0,255,0));//green color
        ui->lineEditStep->setPalette(p);
    }
}


/** \brief Frequency up button clicked.
  *
  * This slot is called when the frequency UP button is clicked.
  * It increments the current frequency with the step and calls the
  * textChanged() slot of the frequency editor, which in turn will also set
  * the frequency of the FCD.
  */
void MainWindow::on_pushButtonUp_clicked()
{
    double dStep = StrToDouble(ui->lineEditStep->text());
    double dFreq = StrToDouble(ui->lineEditFreq->text());

    dFreq += dStep;

    if (dFreq<0.0)
    {
        dFreq = 0.0;
    }

    if (dFreq>2000000000.0)
    {
        dFreq = 2000000000.0;
    }

    ui->lineEditFreq->setText(QLocale(QLocale()).toString(dFreq,'f',0));
}


/** \brief Frequency down button clicked.
  *
  * This slot is called when the frequency DOWN button is clicked.
  * It increments the current frequency with the step and calls the
  * textChanged() slot of the frequency editor, which in turn will also set
  * the frequency of the FCD.
  */
void MainWindow::on_pushButtonDown_clicked()
{
    double dStep = StrToDouble(ui->lineEditStep->text());
    double dFreq = StrToDouble(ui->lineEditFreq->text());

    dFreq -= dStep;

    if (dFreq<0.0)
    {
        dFreq = 0.0;
    }

    if (dFreq>2000000000.0)
    {
        dFreq = 2000000000.0;
    }

    ui->lineEditFreq->setText(QLocale(QLocale()).toString(dFreq,'f',0));
}


/** \brief Frequency correction changed.
  * \param n New correction value in ppm.
  *
  * This slot is called when the value of the frequency correction spin button
  * is changed.
  */
void MainWindow::on_spinBoxCorr_valueChanged(int n)
{
    double d = StrToDouble(ui->lineEditFreq->text());

    d *= 1.0 + n/1000000.0;

    fcdAppSetFreqkHz((int)(d/1000.0));
}


/** \brief Action: About Qthid
  *
  * This slot is called when the user activates the
  *   Help|About menu item (or Qthid|About on Mac)
  */
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About Qthid"),
                       tr("<p>Qthid is a simple controller application for the Funcube Dongle "
                          "software defined radio receiver for 64 MHz - 1.7 GHz.</p>"
                          "<p>Qthid can "
                          "be used to upload new firmware and to set various parameters "
                          "such as frequency, gain, filters, etc.</p>"
                          "<p>Qthid is written using the Qt toolkit (see About Qt) and is avaialble "
                          "for Linux, Mac and Windows. You can download the latest version from the "
                          "<a href='http://www.oz9aec.net/index.php/funcube-dongle/qthid-fcd-controller'>Qthid website</a>."
                          "</p>"
                          "<p>"
                          "<a href='http://funcubedongle.com/'>Funcube Dongle website</a><br/>"
                          "<a href='http://funcube.org.uk/'>Information about Funcube</a>"
                          "</p>"));
}

/** \brief Action: About Qt
  *
  * This slot is called when the user activates the
  *   Help|About Qt menu item (or Qthid|About Qt on Mac)
  */
void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::on_comboBoxLNAGain_activated(int index)
{
    quint8 u8Write = _acs[0].pacis[index].u8Val;
    fcdAppSetParam(_acs[0].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxLNAEnhance_activated(int index)
{
    quint8 u8Write = _acs[1].pacis[index].u8Val;
    fcdAppSetParam(_acs[1].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxRfFilter_activated(int index)
{
    quint8 u8Write = _acs[3].pacis[index].u8Val;
    fcdAppSetParam(_acs[3].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxMixerGain_activated(int index)
{
    quint8 u8Write = _acs[4].pacis[index].u8Val;
    fcdAppSetParam(_acs[4].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxBiasCurrent_activated(int index)
{
    quint8 u8Write = _acs[5].pacis[index].u8Val;
    fcdAppSetParam(_acs[5].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxMixerFilter_activated(int index)
{
    quint8 u8Write = _acs[6].pacis[index].u8Val;
    fcdAppSetParam(_acs[6].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxIFGain1_activated(int index)
{
    quint8 u8Write = _acs[7].pacis[index].u8Val;
    fcdAppSetParam(_acs[7].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxIFGainMode_activated(int index)
{
    quint8 u8Write = _acs[8].pacis[index].u8Val;
    fcdAppSetParam(_acs[8].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxIFRCFilter_activated(int index)
{
    quint8 u8Write = _acs[9].pacis[index].u8Val;
    fcdAppSetParam(_acs[9].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxIFGain2_activated(int index)
{
    quint8 u8Write = _acs[10].pacis[index].u8Val;
    fcdAppSetParam(_acs[10].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxIFGain3_activated(int index)
{
    quint8 u8Write = _acs[11].pacis[index].u8Val;
    fcdAppSetParam(_acs[11].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxIFGain4_activated(int index)
{
    quint8 u8Write = _acs[12].pacis[index].u8Val;
    fcdAppSetParam(_acs[12].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxIFFilter_activated(int index)
{
    quint8 u8Write = _acs[13].pacis[index].u8Val;
    fcdAppSetParam(_acs[13].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxIFGain5_activated(int index)
{
    quint8 u8Write = _acs[14].pacis[index].u8Val;
    fcdAppSetParam(_acs[14].u8CommandSet, &u8Write, 1);
}

void MainWindow::on_comboBoxIFGain6_activated(int index)
{
    quint8 u8Write = _acs[15].pacis[index].u8Val;
    fcdAppSetParam(_acs[15].u8CommandSet,&u8Write,1);
}

void MainWindow::on_pushButtonDefaults_clicked()
{
    COMBOSTRUCT *pcs=_acs;

    while (pcs->pacis!=NULL)
    {
        quint8 u8Write = pcs->pacis[pcs->nIdxDefault].u8Val;
        fcdAppSetParam(pcs->u8CommandSet, &u8Write, 1);
        pcs++;
    }

    ReadDevice();
}

void MainWindow::on_doubleSpinBoxDCI_valueChanged(double value)
{
    union {
        unsigned char auc[4];
        struct {
            qint16 dci;
            qint16 dcq;
        };
    } dcinfo;

    dcinfo.dci = static_cast<signed short>(value*32768.0);
    dcinfo.dcq = static_cast<signed short>(ui->doubleSpinBoxDCQ->value()*32768.0);

    fcdAppSetParam(FCD_HID_CMD_SET_DC_CORR, dcinfo.auc, 4);
}

void MainWindow::on_doubleSpinBoxDCQ_valueChanged(double value)
{
    union {
        unsigned char auc[4];
        struct {
            qint16 dci;
            qint16 dcq;
        };
    } dcinfo;

    dcinfo.dci = static_cast<signed short>(ui->doubleSpinBoxDCI->value()*32768.0);
    dcinfo.dcq = static_cast<signed short>(value*32768.0);

    fcdAppSetParam(FCD_HID_CMD_SET_DC_CORR, dcinfo.auc, 4);
}

void MainWindow::on_doubleSpinBoxPhase_valueChanged(double value)
{
    union {
        unsigned char auc[4];
        struct {
            qint16 phase;
            qint16 gain;
        };
    } iqinfo;

    iqinfo.phase = static_cast<signed short>(value*32768.0);
    iqinfo.gain = static_cast<signed short>(ui->doubleSpinBoxGain->value()*32768.0);

    fcdAppSetParam(FCD_HID_CMD_SET_DC_CORR, iqinfo.auc, 4);
}

void MainWindow::on_doubleSpinBoxGain_valueChanged(double value)
{
    union {
        unsigned char auc[4];
        struct {
            qint16 phase;
            qint16 gain;
        };
    } iqinfo;

    iqinfo.phase = static_cast<signed short>(ui->doubleSpinBoxPhase->value()*32768.0);
    iqinfo.gain = static_cast<signed short>(value*32768.0);

    fcdAppSetParam(FCD_HID_CMD_SET_IQ_CORR, iqinfo.auc, 4);
}
