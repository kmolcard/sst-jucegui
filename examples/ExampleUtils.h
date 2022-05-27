//
// Created by Paul Walker on 5/25/22.
//

#ifndef SST_JUCEGUI_EXAMPLEUTILS_H
#define SST_JUCEGUI_EXAMPLEUTILS_H

#include <juce_gui_basics/juce_gui_basics.h>
#include <sst/jucegui/data/Continuous.h>

struct Solid : public juce::Component
{
    juce::Colour color;
    Solid(const juce::Colour &c) : color(c) {}
    void paint(juce::Graphics &g) override
    {
        if (isHover)
            g.fillAll(color);
    }
    void mouseEnter(const juce::MouseEvent &) override
    {
        isHover = true;
        repaint();
    }
    void mouseExit(const juce::MouseEvent &) override
    {
        isHover = false;
        repaint();
    }
    bool isHover{false};
};

struct ConcreteCM : sst::jucegui::data::ContinunousModulatable
{
    std::string label{"A Knob"};
    std::string getLabel() const override { return label; }
    float value{0};
    float getValue() const override { return value; }
    void setValueFromGUI(const float &f) override
    {
        value = f;
        std::cout << __FILE__ << ":" << __LINE__ << " setValueFromGUI=" << value << std::endl;

        for (auto *l : guilisteners)
            l->dataChanged();
        for (auto *l : modellisteners)
            l->dataChanged();
    }
    void setValueFromModel(const float &f) override
    {
        value = f;
        for (auto *l : guilisteners)
            l->dataChanged();
    }

    float min{0}, max{1};
    float getMin() const override { return min; }
    float getMax() const override { return max; }

    float mv{0.2};
    float getModulationValuePM1() const override { return mv; }
    void setModulationValuePM1(const float &f) override { mv = f; }
    bool isModulationBipolar() override { return isBipolar(); } // sure why not
};
#endif // SST_JUCEGUI_EXAMPLEUTILS_H
