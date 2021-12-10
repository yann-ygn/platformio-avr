#include "hardware.h"

Memory mem(0);

Encoder selector(12, 13);
TemporarySwitch selectorSwitch(14, 1000);
TemporarySwitch editSwitch(11, 1000);
Led editSwitchLed(10);

TemporarySwitch presetUpFsw(24, 1000);
TemporarySwitch presetDownFsw(25, 1000);
TemporarySwitch preset1Fsw(26, 1000);
TemporarySwitch preset2Fsw(27, 1000);
TemporarySwitch preset3Fsw(28, 1000);
TemporarySwitch preset4Fsw(29, 1000);

Preset presetBank[c_maxPresets];
Loops presetLoops[c_maxPresets];

MenuItem preset[] =
{
    MenuItemTwoIntFullScreenHeader("Preset"),
    MenuItemTwoIntFullScreen(),
    MenuItemTwoIntFullScreen(),
    MenuItemFooter()
};

Menu presetMenu(128, 64, 7, 9, 2, false);

void Hardware::hardwareSetup()
{
    Serial.begin(115200);
    delay(500);
    mem.memorySetup();
    selector.encoderSetup();
    selectorSwitch.tempSwitchSetup();
    editSwitch.tempSwitchSetup();
    editSwitchLed.ledSetup();
    presetUpFsw.tempSwitchSetup();
    presetDownFsw.tempSwitchSetup();
    preset1Fsw.tempSwitchSetup();
    preset2Fsw.tempSwitchSetup();
    preset3Fsw.tempSwitchSetup();
    preset4Fsw.tempSwitchSetup();
}

void Hardware::hardwarePoll()
{
    if (m_presetMenuDisplay)
    {
        presetUpFsw.tempSwitchPoll();
        if (presetUpFsw.tempSwitchPushed())
        {
            m_presetUpFswPress = true;
        }
        presetDownFsw.tempSwitchPoll();
        preset1Fsw.tempSwitchPoll();
        preset2Fsw.tempSwitchPoll();
        preset3Fsw.tempSwitchPoll();
        preset4Fsw.tempSwitchPoll();
        editSwitch.tempSwitchPoll();
    }
    else
    {
        selectorSwitch.tempSwitchPoll();
        selector.encoderPoll();
    }
}

void Hardware::hardwareStartup()
{
    selectorSwitch.tempSwitchPoll();
    selector.encoderPoll();
    editSwitch.tempSwitchPoll();
    presetUpFsw.tempSwitchPoll();
    presetDownFsw.tempSwitchPoll();
    preset1Fsw.tempSwitchPoll();
    preset2Fsw.tempSwitchPoll();
    preset3Fsw.tempSwitchPoll();
    preset4Fsw.tempSwitchPoll();
    delay(500);
}

void Hardware::restoreLastState()
{
    m_currentPresetBank = mem.readCurrentPresetBank();
    m_currentPreset = mem.readCurrentPreset();
    loadPresetBank();
    p_currentPreset = &presetBank[m_currentPreset];
}

void Hardware::resetHardwareTriggers()
{
    m_selectorMove = false;
    m_selectorSwitchPress = false;
    m_selectorSwitchLongPress = false;
    m_editSwitchPress = false;
    m_editSwitchLongPress = false;
    m_presetUpFswPress = false;
    m_presetUpFswLongPress = false;
    m_presetDownFswPress = false;
    m_presetDownFswLongPress = false;
    m_preset1FswPress = false;
    m_preset2FswPress = false;
    m_preset3FswPress = false;
    m_preset4FswPress = false;
}

void Hardware::menuSetup()
{
    preset[1].setMenuItemIntValue(&m_currentPresetBank);
    preset[2].setMenuItemIntValue(&m_currentPreset);
    presetMenu.menuSetup(preset);
}

void Hardware::loadPresetBank()
{
    for (uint8_t i = 0; i < c_maxPresets; i++)
    {
        presetBank[i].presetSetup(m_currentPresetBank, i, &presetLoops[i], c_maxLoops);
        mem.readPreset(presetBank[i].getBank(), presetBank[i].getPreset(), presetBank[i].getLoops(), presetBank[i].getLoopsStates(), c_maxLoops);
    }
}

bool Hardware::getSelectorMove()
{
    return m_selectorMove;
}

bool Hardware::getSelectorwitchPress()
{
    return m_selectorSwitchPress;
}

bool Hardware::getSelectorSwitchLongPress()
{
    return m_selectorSwitchLongPress;
}

bool Hardware::getEditSwitchPress()
{
    return m_editSwitchPress;
}

bool Hardware::getEditSwitchLongPress()
{
    return m_editSwitchLongPress;
}

bool Hardware::getPresetMenuDisplay()
{
    return m_presetMenuDisplay;
}

bool Hardware::getPresetEditMenuDisplay()
{
    return m_presetEditMenuDisplay;
}

bool Hardware::getPresetLoopEditMenuDisplay()
{
    return m_presetLoopEditMenuDisplay;
}

bool Hardware::getMainMenuDisplay()
{
    return m_mainMenuDisplay;
}