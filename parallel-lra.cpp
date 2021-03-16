#include "z3++.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace z3;

void params_bmc(params &p) {
    p.set("fp.engine", "bmc");
}

void params_gspacer(params &p) {
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
    p.set("fp.spacer.global", true);
    p.set("fp.spacer.concretize", true);
    p.set("fp.spacer.conjecture", true);
    p.set("fp.spacer.expand_bnd", true);
}

//TODO: set return status properly
//TODO: handle setting of wrong timeout better
int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    context c;
    params gspc(c), bmc(c);
    params_gspacer(gspc);
    params_bmc(bmc);

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
    tactics.push_back(with(tactic(c, "horn"), gspc));
    tactics.push_back(with(tactic(c, "horn"), bmc));
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
