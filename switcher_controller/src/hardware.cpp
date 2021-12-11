#include "hardware.h"

Memory mem(0);

Encoder selector(12, 13);
TemporarySwitch selectorSwitch(14, 1000);
TemporarySwitch editSwitch(11, 1000);
Led editSwitchLed(10);

TemporarySwitch presetUpFsw(24, 1000);
TemporarySwitch presetDownFsw(25, 1000);
TemporarySwitch preset0Fsw(26, 1000);
TemporarySwitch preset1Fsw(27, 1000);
TemporarySwitch preset2Fsw(28, 1000);
TemporarySwitch preset3Fsw(29, 1000);

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
    preset0Fsw.tempSwitchSetup();
    preset1Fsw.tempSwitchSetup();
    preset2Fsw.tempSwitchSetup();
    preset3Fsw.tempSwitchSetup();

    //mem.memoryReset();
}

void Hardware::hardwarePoll()
{
    if (m_presetMenuDisplay)
    {
        presetUpFsw.tempSwitchPoll();
        if (presetUpFsw.tempSwitchPushed())
        {
            m_currentPresetBank++;
            m_currentPreset = 0;
            m_presetUpFswPress = true;
        }
        if (presetUpFsw.tempSwitchLongPress())
        {
            m_presetUpFswLongPress = true;
        }

        presetDownFsw.tempSwitchPoll();
        if (presetDownFsw.tempSwitchPushed())
        {
            m_currentPresetBank--;
            m_currentPreset = 0;
            m_presetDownFswPress = true;
        }
        if (presetDownFsw.tempSwitchLongPress())
        {
            m_presetDownFswLongPress = true;
        }

        preset0Fsw.tempSwitchPoll();
        if (preset0Fsw.tempSwitchPushed())
        {
            m_currentPreset = 0;
            m_preset0FswPress = true;
        }

        preset1Fsw.tempSwitchPoll();
        if (preset1Fsw.tempSwitchPushed())
        {
            m_currentPreset = 1;
            m_preset1FswPress = true;
        }

        preset2Fsw.tempSwitchPoll();
        if (preset2Fsw.tempSwitchPushed())
        {
            m_currentPreset = 2;
            m_preset2FswPress = true;
        }

        preset3Fsw.tempSwitchPoll();
        if (preset3Fsw.tempSwitchPushed())
        {
            m_currentPreset = 3;
            m_preset2FswPress = true;
        }

        editSwitch.tempSwitchPoll();
        if (editSwitch.tempSwitchPushed())
        {
            m_editSwitchPress = true;
        }
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
    preset0Fsw.tempSwitchPoll();
    preset1Fsw.tempSwitchPoll();
    preset2Fsw.tempSwitchPoll();
    preset3Fsw.tempSwitchPoll();
    delay(500);
}

void Hardware::restoreLastState()
{
    m_currentPresetBank = mem.readCurrentPresetBank();
    m_currentPreset = mem.readCurrentPreset();
    loadPresetBank();
    p_currentPreset = &presetBank[m_currentPreset];
    m_presetMenuDisplay = true;
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
    m_preset0FswPress = false;
    m_preset1FswPress = false;
    m_preset2FswPress = false;
    m_preset3FswPress = false;
}

void Hardware::menuSetup()
{
    preset[1].setMenuItemIntValue(&m_currentPresetBank);
    preset[2].setMenuItemIntValue(p_currentPreset->getPreset());
    presetMenu.menuSetup(preset);
}

void Hardware::loadPresetBank()
{
    if (m_currentPresetBank > (c_firstPresetBank + c_maxPresetBanks))
    {
        m_currentPresetBank = c_firstPresetBank;
    }
    if (m_currentPresetBank < c_firstPresetBank)
    {
        m_currentPresetBank = c_firstPresetBank + c_maxPresetBanks;
    }

    for (uint8_t i = 0; i < c_maxPresets; i++)
    {
        presetBank[i].presetSetup(m_currentPresetBank, i, &presetLoops[i], c_maxLoops);
        mem.readPreset(presetBank[i].getBank(), presetBank[i].getPreset(), presetBank[i].getLoops(), presetBank[i].getLoopsStates(), c_maxLoops);
    }

    p_currentPreset = &presetBank[0];
    m_currentPreset = 0;
    presetMenu.menuRefresh();
}

void Hardware::loadPreset()
{
    Serial.println(m_currentPreset);
    p_currentPreset = &presetBank[m_currentPreset];

    Serial.println(p_currentPreset->getBank());
    Serial.println(*p_currentPreset->getPreset());

    presetMenu.menuRefresh();
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

bool Hardware::getPresetUpFswPress()
{
    return m_presetUpFswPress;
}

bool Hardware::getPresetDownFswPress()
{
    return m_presetDownFswPress;
}

bool Hardware::getPreset0FswPress()
{
    return m_preset0FswPress;
}

bool Hardware::getPreset1FswPress()
{
    return m_preset1FswPress;
}

bool Hardware::getPreset2FswPress()
{
    return m_preset2FswPress;
}

bool Hardware::getPreset3FswPress()
{
    return m_preset3FswPress;
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