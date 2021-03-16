#include "z3++.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace z3;
void params_gg(params &p) {
    p.set("fp.spacer.global", true);
    p.set("fp.spacer.concretize", true);
    p.set("fp.spacer.conjecture", true);
    p.set("fp.spacer.expand_bnd", true);
    p.set("fp.spacer.ground_pobs", false);
    p.set("fp.spacer.q3.use_qgen", true);
    p.set("fp.spacer.q3.instantiate", true);
    p.set("fp.spacer.q3", true);
}

void params_qgen(params &p) {
    p.set("fp.spacer.global", false);
    p.set("fp.spacer.concretize", false);
    p.set("fp.spacer.conjecture", false);
    p.set("fp.spacer.ground_pobs", false);
    p.set("fp.spacer.q3.use_qgen", true);
    p.set("fp.spacer.q3.instantiate", true);
    p.set("fp.spacer.q3", true);
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
void params_timeout(params &p, unsigned time) {
    p.set("timeout", time);
}

//TODO: set return status properly
//TODO: handle setting of wrong timeout better
int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    context c;
    params gg(c), qgen(c);
    //add default spacer args
    params_spacer(gg);
    params_spacer(qgen);
    //gg works in combination with qgen
    params_gg(gg);

    //have qgen without gg
    params_qgen(qgen);

    std::ofstream op_file;
    if (argc >= 3) {
        char* op_fname = argv[2];
        op_file.open (op_fname);
    }

    if (argc >= 4) {
        int timeout = atoi(argv[3]);
        c.set("timeout", (int)timeout * 1000);
    }

    std::vector<tactic> tactics;
    tactics.push_back(with(tactic(c, "horn"), gg));
    tactics.push_back(with(tactic(c, "horn"), qgen));
    tactic t = par_or(2, tactics.data());
    solver s = t.mk_solver();
    expr_vector assertions = c.parse_file(argv[1]);
    s.add(assertions);
    check_result res = s.check();
    if (op_file.is_open())
        op_file << res << "\n";
    else
        std::cout << res << "\n";
    return 0;
}
