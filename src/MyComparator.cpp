#include "plugin.hpp"

struct MyComparator : Module {
  enum ParamIds {
    NUM_PARAMS,
  };
  enum InputIds {
    INPUTA1,
    INPUTB1,
    INPUTA2,
    INPUTB2,
    NUM_INPUTS,
  };
  enum OutputIds {
    OUTPUT1,
    OUTPUT2,
    NUM_OUTPUTS,
  };
  enum LightsIds {
    LIGHT_1,
    LIGHT_2,
    NUM_LIGHTS,
  };

  MyComparator() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  }

  void process(const ProcessArgs &args) override;
};


void MyComparator::process(const ProcessArgs &args) {
  if (inputs[INPUTA1].isConnected() && inputs[INPUTB1]. isConnected()) {
    float out = inputs[INPUTA1].getVoltage() >= inputs[INPUTB1].getVoltage();
    outputs[OUTPUT1].setVoltage(10.f * out);
    lights[OUTPUT1].setBrightness(out);
  }
}

struct MyComparatorWidget : ModuleWidget {

  MyComparatorWidget(MyComparator* module) {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MyComparator.svg")));

    addInput(createInput<PJ301MPort>(Vec(50, 78), module, MyComparator::INPUTA1));
    addInput(createInput<PJ301MPort>(Vec(50, 108), module, MyComparator::INPUTB1));

    addOutput(createOutput<PJ3410Port>(Vec(46, 138), module, MyComparator::OUTPUT1));

    addChild(createLight<TinyLight<GreenLight>>(Vec(80, 150), module, MyComparator::LIGHT_1));
  }
};

Model * modelMyComparator = createModel<MyComparator, MyComparatorWidget>("MyComparator");
