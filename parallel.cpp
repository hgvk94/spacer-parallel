#include "z3++.h"
#include <vector>
using namespace z3;
void params_gg(params &p) {
    p.set("fp.spacer.global", true);
    p.set("fp.spacer.concretize", true);
    p.set("fp.spacer.conjecture", true);
    p.set("fp.spacer.expand_bnd", true);
}

void params_qgen(params &p) {
    p.set("fp.spacer.q3.use_qgen", true);
    p.set("fp.spacer.q3.instantiate", true);
    p.set("fp.spacer.q3", true);
    p.set("fp.spacer.q3.use_qgen", true);
}

void params_array(params &p) {
    p.set("fp.spacer.ground_pobs", false);
}

void params_spacer(params &p) {
    p.set("fp.engine", "spacer");
    p.set("fp.spacer.use_sage", false);
    p.set("fp.xform.slice", true);
    p.set("fp.xform.inline_linear", true);
    p.set("fp.xform.inline_eager", true);
    p.set("fp.xform.tail_simplifier_pve", false);
    p.set("fp.print_statistics", true);
    p.set("fp.spacer.elim_aux", true);
    p.set("fp.spacer.reach_dnf", true);
    p.set("fp.spacer.iuc", (unsigned)1);
    p.set("fp.spacer.iuc.arith", (unsigned)1);
    p.set("fp.validate", true);
    p.set("fp.spacer.mbqi", false);
    p.set("fp.spacer.iuc.print_farkas_stats", false);
    p.set("fp.spacer.iuc.old_hyp_reducer", false);
    p.set("fp.spacer.ctp", true);
    p.set("fp.spacer.native_mbp", true);
    p.set("fp.spacer.use_iuc", true);
}

//TODO: set return status properly
int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }
    context c;
    params p(c), q(c);
    params_spacer(p);
    params_spacer(q);
    params_gg(p);
    params_qgen(q);
    std::vector<tactic> tactics;
    tactics.push_back(with(tactic(c, "horn"), p));
    tactics.push_back(with(tactic(c, "horn"), q));
    tactic t = par_or(2, tactics.data());
    solver s = t.mk_solver();
    expr_vector assertions = c.parse_file(argv[1]);
    s.add(assertions);
    std::cout << s.check() << "\n";
    return 0;
}
