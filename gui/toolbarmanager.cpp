#include "toolbarmanager.h"

ToolbarManager::ToolbarManager(QObject *parent) : QObject(parent) {
    mainWindow = (MainWindow*)parent;
    gameDataContainer = GameDataContainer::Instance();

    vitalsIndicator = new VitalsIndicator(this);
    statusIndicator = new StatusIndicator(this);
    quickButtonDisplay = new QuickButtonDisplay(this);
    wieldLeft = new WieldIndicator(this, LHAND_ICO);
    wieldRight = new WieldIndicator(this, RHAND_ICO);
    spell = new SpellIndicator(this);
}

void ToolbarManager::loadToolbar() {
    mainWindow->setToolbarAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);

    QWidget* wieldLeftWidget = wieldLeft->create();
    wieldLeftWidget->setContentsMargins(QMargins(20, 0, 0, 0));
    mainWindow->addToolbarWidget(wieldLeftWidget);
    mainWindow->addToolbarWidget(wieldRight->create());
    mainWindow->addToolbarWidget(spell->create());
    //mainWindow->addToolbarSeparator();

    mainWindow->addToolbarWidget(statusIndicator->create());
    //mainWindow->addToolbarSeparator();

    mainWindow->addToolbarWidget(quickButtonDisplay->create());
    //mainWindow->addToolbarSeparator();

    /*QWidget* spacerWidget = new QWidget;
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    mainWindow->addToolbarWidget(spacerWidget);*/

    mainWindow->addToolbarWidget(vitalsIndicator->create());
}

void ToolbarManager::updateWieldLeft(QString value) {
    wieldLeft->textLabel->setText(value);
}

void ToolbarManager::updateWieldRight(QString value) {
    wieldRight->textLabel->setText(value);
}

void ToolbarManager::updateSpell(QString toolTip) {
    spell->imageLabel->setToolTip(toolTip);
}

QHash<QString, bool> ToolbarManager::getStatus() {
    return statusIndicator->getFullStatus();
}

void ToolbarManager::updateVitals(QString name, QString value) {
    int intValue = value.toInt();
    if(name == "health") {
        gameDataContainer->setHealth(intValue);
        vitalsIndicator->healthBar->setValue(intValue);
        vitalsIndicator->healthBar->setToolTip("Health: " + value + "%");
        vitalsIndicator->healthBar->repaint();
    } else if(name == "concentration") {
        gameDataContainer->setConcentration(intValue);
        vitalsIndicator->concentrationBar->setValue(intValue);
        vitalsIndicator->concentrationBar->setToolTip("Concentration: " + value + "%");
        vitalsIndicator->concentrationBar->repaint();
    } else if(name == "stamina") {
        gameDataContainer->setFatigue(intValue);
        vitalsIndicator->fatigueBar->setValue(intValue);
        vitalsIndicator->fatigueBar->setToolTip("Fatigue: " + value + "%");
        vitalsIndicator->fatigueBar->repaint();
    } else if(name == "spirit") {
        gameDataContainer->setSpirit(intValue);
        vitalsIndicator->spiritBar->setValue(intValue);
        vitalsIndicator->spiritBar->setToolTip("Spirit: " + value + "%");
        vitalsIndicator->spiritBar->repaint();
    }
}

void ToolbarManager::updateStatus(QString visible, QString icon) {
    statusIndicator->updateStatus(visible, icon);
}

int ToolbarManager::getHealthValue() {
    return vitalsIndicator->healthBar->value();
}

int ToolbarManager::getConcentrationValue() {
    return vitalsIndicator->concentrationBar->value();
}

int ToolbarManager::getFatigueValue() {
    return vitalsIndicator->fatigueBar->value();
}

int ToolbarManager::getSpiritValue() {
    return vitalsIndicator->spiritBar->value();
}

void ToolbarManager::quickButtonAction() {
    QToolButton *button = (QToolButton *)sender();

    mainWindow->getCommandLine()->setText(button->text());
    emit mainWindow->getCommandLine()->sendCommand();
}

ToolbarManager::~ToolbarManager() {
    delete vitalsIndicator;
    delete statusIndicator;
    delete quickButtonDisplay;
    delete wieldLeft;
    delete wieldRight;
}