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

LedDriver16 presetLed(1);

Preset presetBank[c_maxPresets];
Loops presetLoops[c_maxPresets];

extern MenuItem presetEdit[];
extern MenuItem presetEditLoops[];

MenuItem preset[] =
{
    MenuItemTwoIntFullScreenHeader("Preset"),
    MenuItemTwoIntFullScreen(),
    MenuItemTwoIntFullScreen(),
    MenuItemFooter()
};

MenuItem presetEdit[] =
{
    MenuItemHeader("Edit menu"),
    MenuItemSubMenu("Loops setup", presetEditLoops),
    MenuItemSubMenu("MIDI setup", presetEditLoops),
    MenuItemFooter()
};

MenuItem presetEditLoops[] =
{
    MenuItemListIntToggleHeader("Loops setup"),
    MenuItemListIntToggle(),
    MenuItem(),
    MenuItem(),
    MenuItem(),
    MenuItem(),
    MenuItemSubMenuBack("Back", presetEdit),
    MenuItemFooter()
};

Menu presetMenu(128, 64, 7, 9, 1, false);
Menu presetEditMenu(128, 64, 7, 9, 1);

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
    presetLed.ledDriverSetup();

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
    else if (m_presetEditMenuDisplay)
    {
        selectorSwitch.tempSwitchPoll();

        if (selector.encoderPoll())
        {
            m_selectorMove = true;
        }

        if (selectorSwitch.tempSwitchPushed())
        {
            m_selectorSwitchPress = true;
        }
    }
    else
    {

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
}

void Hardware::restoreLastState()
{
    presetLed.setLedStateByMask(0x3);
    m_currentPresetBank = mem.readCurrentPresetBank();
    m_currentPreset = mem.readCurrentPreset();
    p_currentPreset = &presetBank[m_currentPreset];
    loadPresetBank();
    displayPresetMenu();
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

void Hardware::processSelector()
{
    if (selector.getEncoderState() == c_encoderIncrement)
    {
        p_currentMenu->menuCursorUp();
    }
    else if (selector.getEncoderState() == c_encoderDrecrement)
    {
        p_currentMenu->menuCursorDown();
    }
}

void Hardware::processSelectorSwitch()
{
    if (p_currentMenu->getCurrentItemType() == c_menuItemTypeSubMenu ||
        p_currentMenu->getCurrentItemType() == c_menuItemTypeSubMenuBack )
    {
        p_currentMenu->menuCursorEnter();
    }
}

void Hardware::menuSetup()
{
    presetEditMenu.menuSetup(presetEdit, false);
    presetMenu.menuSetup(preset, false);
}

void Hardware::resetMenuStates()
{
    m_presetMenuDisplay = false;
    m_presetEditMenuDisplay = false;
    m_presetLoopEditMenuDisplay = false;
    m_mainMenuDisplay = false;
}

void Hardware::displayPresetMenu()
{
    m_presetMenuDisplay = true;
    preset[1].setMenuItemIntValue(&m_currentPresetBank);
    preset[2].setMenuItemIntValue(p_currentPreset->getPreset());
    p_currentMenu = &presetMenu;
    p_currentMenu->menuRefresh();
}

void Hardware::displayPresetEditMenu()
{
    resetMenuStates();
    m_presetEditMenuDisplay = true;
    editSwitchLed.ledTurnOn();
    p_currentMenu = &presetEditMenu;
    p_currentMenu->menuRefresh();
}

void Hardware::loadPresetBank()
{
    mem.writeCurrentPresetBank(m_currentPresetBank);

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

    //p_currentPreset = &presetBank[0];
    //m_currentPreset = 0;

    loadPreset();
}

void Hardware::loadPreset()
{
    p_currentPreset = &presetBank[m_currentPreset];

    mem.writeCurrentPreset(*p_currentPreset->getPreset());

    preset[2].setMenuItemIntValue(p_currentPreset->getPreset());
    presetEditLoops[1].setMenuItemListIntToggleList(p_currentPreset->getLoops());
    presetEditLoops[1].setMenuItemListIntToggleState(p_currentPreset->getLoopsStates());
    presetEditLoops[1].setMenuItemListIntToggleCount(c_maxLoops);

    presetLed.setLedStateByMask(0x3 + (1 << (m_currentPreset + 2)));

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