#ifndef K4SIMDELPHES_PYTHIAEVTGEN_INTERFACE_H
#define K4SIMDELPHES_PYTHIAEVTGEN_INTERFACE_H 1

// Include files

// Pythia
#include "Pythia.h"
#include "Pythia8Plugins/CombineMatchingInput.h"
#include "Pythia8Plugins/EvtGen.h"

// EvtGen
#include "EvtGen/EvtGen.hh"
#include "EvtGenBase/EvtAbsRadCorr.hh"
#include "EvtGenBase/EvtDecayBase.hh"
#include "EvtGenBase/EvtMTRandomEngine.hh"

// std
#include <cstdlib>
#include <memory>

/** @class PythiaEvtGen_Interface PythiaEvtGen_Interface.h k4simdelphes/PythiaEvtGen_Interface.h
 *
 *
 *  @author Jihyun Bhom, Marcin Chrzaszcz
 *  @date   2020-12-07
 */
class PythiaEvtGen_Interface {
public:
  /// Standard constructor. EvtGen (and Photos/Tauola) draw their random numbers from the random number generator of
  /// the passed Pythia instance, so they follow its seed (Random:seed)
  PythiaEvtGen_Interface(Pythia8::Pythia* p, std::string pdf, std::string evt_pdl);

  virtual ~PythiaEvtGen_Interface(); ///< Destructor

  // void add_decays(std::string decayfile, int seed, int motherID);
  // void add_decays(std::string decayfile, int motherID);
  void add_decays(std::string decayfile, int motherID, std::string name);

  void add_inclusive(std::string decayfile);

  void decay_signals();
  void decay();

  bool check_Signal_Appereance();
  void set_debug(bool t = true) { debug = t; };
  void set_verbose(bool t = true) { verbose = t; };

  void set_regenerate(bool t = true) { regenerate = t; };

  void UpdatePythiaEvent(Pythia8::Particle* part1, EvtParticle* Evtpart);

  void set_rehadronize(int i) { n_rehadronize = i; };

protected:
private:
  //  std::vector<EvtGen*> EG_gens;
  EvtGen* evtgen;
  std::vector<int> motherIDs;
  std::vector<std::string> sig_names;
  Pythia8::Pythia* pythia;
  std::string particleDataFile;
  /// EvtGen random engine wrapping the Pythia random number generator
  std::unique_ptr<Pythia8::EvtGenRandom> rndmEngine;

  std::string pdl;
  // int **signal_map;
  std::vector<std::vector<int>> signal_map;

  std::vector<int> NOfSignal_list;

  bool debug;
  std::vector<int> B_ids;
  bool verbose;

  bool regenerate;
  int n_rehadronize; // number of tries to rehadronize before regenerating
};
#endif // K4SIMDELPHES_PYTHIAEVTGEN_INTERFACE_H
