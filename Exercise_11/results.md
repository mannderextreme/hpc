# 11.1 Pragmas

    #pragma clang loop vectorize(assume_safety):
    -O2 evaluates all code, if the compiler assumes there is a dependency, vectorization is not performed. 
    If we, the programmers, know that there is no dependency, we can tell the compiler by using this pragma.
    If put into our code the compiler will vectorize the following loop.


# 11.2 Generating vectorization reports

Both g++ and clang++ already produce SVE instructions for triad_simple.

## 11.2.1 Vectorization report g++

    [hgf_rlx5119@ftp-a64n1 Exercise_11]$ make gemm_asm_sve 
    g++ -g -pedantic -Wall -Wextra -Werror -O2 -fopenmp -ftree-vectorize -fopt-info-vec-all -c kernels/triad.cpp -o ./build/kernels/triad.o
    kernels/triad.cpp:3:7: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:4:17: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:4:17: note: not vectorized: not enough data-refs in basic block.

    Analyzing loop at kernels/triad.cpp:11
    kernels/triad.cpp:11:32: note: ===== analyze_loop_nest =====
    kernels/triad.cpp:11:32: note: === vect_analyze_loop_form ===
    kernels/triad.cpp:11:32: note: === get_loop_niters ===
    kernels/triad.cpp:11:32: note: Symbolic number of iterations is i_nValues_12(D)
    kernels/triad.cpp:11:32: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:11:32: note: got vectype for stmt: _3 = *_2;
    const vector(4) float
    kernels/triad.cpp:11:32: note: got vectype for stmt: _5 = *_4;
    const vector(4) float
    kernels/triad.cpp:11:32: note: got vectype for stmt: *_7 = _8;
    vector(4) float
    kernels/triad.cpp:11:32: note: === vect_analyze_scalar_cycles ===
    kernels/triad.cpp:11:32: note: Analyze phi: l_va_20 = PHI <0(5), l_va_17(6)>
    kernels/triad.cpp:11:32: note: Access function of PHI: {0, +, 1}_1
    kernels/triad.cpp:11:32: note: step: 1,  init: 0
    kernels/triad.cpp:11:32: note: Detected induction.
    kernels/triad.cpp:11:32: note: Analyze phi: .MEM_21 = PHI <.MEM_11(D)(5), .MEM_16(6)>
    kernels/triad.cpp:11:32: note: === vect_pattern_recog ===
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand l_va_20
    kernels/triad.cpp:11:32: note: def_stmt: l_va_20 = PHI <0(5), l_va_17(6)>
    kernels/triad.cpp:11:32: note: type of def: induction
    kernels/triad.cpp:11:32: note: vect_recog_mult_pattern: detected:
    kernels/triad.cpp:11:32: note: patt_22 = l_va_20 << 2;
    kernels/triad.cpp:11:32: note: mult pattern recognized: patt_22 = l_va_20 << 2;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _5
    kernels/triad.cpp:11:32: note: def_stmt: _5 = *_4;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: === vect_analyze_data_ref_accesses ===
    kernels/triad.cpp:11:32: note: === vect_mark_stmts_to_be_vectorized ===
    kernels/triad.cpp:11:32: note: init: phi relevant? l_va_20 = PHI <0(5), l_va_17(6)>
    kernels/triad.cpp:11:32: note: init: phi relevant? .MEM_21 = PHI <.MEM_11(D)(5), .MEM_16(6)>
    kernels/triad.cpp:11:32: note: init: stmt relevant? # DEBUG l_va => l_va_20
    kernels/triad.cpp:11:32: note: init: stmt relevant? # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: init: stmt relevant? _1 = l_va_20 * 4;
    kernels/triad.cpp:11:32: note: init: stmt relevant? _2 = i_a_13(D) + _1;
    kernels/triad.cpp:11:32: note: init: stmt relevant? _3 = *_2;
    kernels/triad.cpp:11:32: note: init: stmt relevant? _4 = i_b_14(D) + _1;
    kernels/triad.cpp:11:32: note: init: stmt relevant? _5 = *_4;
    kernels/triad.cpp:11:32: note: init: stmt relevant? _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: init: stmt relevant? _7 = o_c_15(D) + _1;
    kernels/triad.cpp:11:32: note: init: stmt relevant? _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: init: stmt relevant? *_7 = _8;
    kernels/triad.cpp:11:32: note: vec_stmt_relevant_p: stmt has vdefs.
    kernels/triad.cpp:11:32: note: mark relevant 5, live 0: *_7 = _8;
    kernels/triad.cpp:11:32: note: init: stmt relevant? # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: init: stmt relevant? l_va_17 = l_va_20 + 1;
    kernels/triad.cpp:11:32: note: init: stmt relevant? # DEBUG l_va => l_va_17
    kernels/triad.cpp:11:32: note: init: stmt relevant? # DEBUG l_va => l_va_17
    kernels/triad.cpp:11:32: note: init: stmt relevant? # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: init: stmt relevant? if (i_nValues_12(D) <= l_va_17)
    kernels/triad.cpp:11:32: note: worklist: examine stmt: *_7 = _8;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _8
    kernels/triad.cpp:11:32: note: def_stmt: _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: mark relevant 5, live 0: _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: worklist: examine stmt: _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _3
    kernels/triad.cpp:11:32: note: def_stmt: _3 = *_2;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: mark relevant 5, live 0: _3 = *_2;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _6
    kernels/triad.cpp:11:32: note: def_stmt: _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: mark relevant 5, live 0: _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: worklist: examine stmt: _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _5
    kernels/triad.cpp:11:32: note: def_stmt: _5 = *_4;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: mark relevant 5, live 0: _5 = *_4;
    kernels/triad.cpp:11:32: note: worklist: examine stmt: _5 = *_4;
    kernels/triad.cpp:11:32: note: worklist: examine stmt: _3 = *_2;
    kernels/triad.cpp:11:32: note: === vect_analyze_data_ref_dependences ===
    kernels/triad.cpp:11:32: note: versioning for alias required: can't determine dependence between *_2 and *_7
    consider run-time aliasing test between *_2 and *_7
    kernels/triad.cpp:11:32: note: versioning for alias required: can't determine dependence between *_4 and *_7
    consider run-time aliasing test between *_4 and *_7
    kernels/triad.cpp:11:32: note: === vect_determine_vectorization_factor ===
    kernels/triad.cpp:11:32: note: ==> examining phi: l_va_20 = PHI <0(5), l_va_17(6)>
    kernels/triad.cpp:11:32: note: ==> examining phi: .MEM_21 = PHI <.MEM_11(D)(5), .MEM_16(6)>
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG l_va => l_va_20
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: _1 = l_va_20 * 4;
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: _2 = i_a_13(D) + _1;
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: _3 = *_2;
    kernels/triad.cpp:11:32: note: get vectype for scalar type:  float
    kernels/triad.cpp:11:32: note: vectype: vector(4) float
    kernels/triad.cpp:11:32: note: nunits = 4
    kernels/triad.cpp:11:32: note: ==> examining statement: _4 = i_b_14(D) + _1;
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: _5 = *_4;
    kernels/triad.cpp:11:32: note: get vectype for scalar type:  float
    kernels/triad.cpp:11:32: note: vectype: vector(4) float
    kernels/triad.cpp:11:32: note: nunits = 4
    kernels/triad.cpp:11:32: note: ==> examining statement: _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: get vectype for scalar type:  float
    kernels/triad.cpp:11:32: note: vectype: vector(4) float
    kernels/triad.cpp:11:32: note: get vectype for scalar type:  float
    kernels/triad.cpp:11:32: note: vectype: vector(4) float
    kernels/triad.cpp:11:32: note: nunits = 4
    kernels/triad.cpp:11:32: note: ==> examining statement: _7 = o_c_15(D) + _1;
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: get vectype for scalar type:  float
    kernels/triad.cpp:11:32: note: vectype: vector(4) float
    kernels/triad.cpp:11:32: note: get vectype for scalar type:  float
    kernels/triad.cpp:11:32: note: vectype: vector(4) float
    kernels/triad.cpp:11:32: note: nunits = 4
    kernels/triad.cpp:11:32: note: ==> examining statement: *_7 = _8;
    kernels/triad.cpp:11:32: note: get vectype for scalar type:  float
    kernels/triad.cpp:11:32: note: vectype: vector(4) float
    kernels/triad.cpp:11:32: note: nunits = 4
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: l_va_17 = l_va_20 + 1;
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG l_va => l_va_17
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG l_va => l_va_17
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: ==> examining statement: if (i_nValues_12(D) <= l_va_17)
    kernels/triad.cpp:11:32: note: skip.
    kernels/triad.cpp:11:32: note: vectorization factor = 4
    kernels/triad.cpp:11:32: note: === vect_analyze_slp ===
    kernels/triad.cpp:11:32: note: === vect_make_slp_decision ===
    kernels/triad.cpp:11:32: note: === vect_analyze_data_refs_alignment ===
    kernels/triad.cpp:11:32: note: recording new base alignment for i_a_13(D)
    kernels/triad.cpp:11:32: note:   alignment:    4
    kernels/triad.cpp:11:32: note:   misalignment: 0
    kernels/triad.cpp:11:32: note:   based on:     _3 = *_2;
    kernels/triad.cpp:11:32: note: recording new base alignment for i_b_14(D)
    kernels/triad.cpp:11:32: note:   alignment:    4
    kernels/triad.cpp:11:32: note:   misalignment: 0
    kernels/triad.cpp:11:32: note:   based on:     _5 = *_4;
    kernels/triad.cpp:11:32: note: recording new base alignment for o_c_15(D)
    kernels/triad.cpp:11:32: note:   alignment:    4
    kernels/triad.cpp:11:32: note:   misalignment: 0
    kernels/triad.cpp:11:32: note:   based on:     *_7 = _8;
    kernels/triad.cpp:11:32: note: vect_compute_data_ref_alignment:
    kernels/triad.cpp:11:32: note: can't force alignment of ref: *_2
    kernels/triad.cpp:11:32: note: vect_compute_data_ref_alignment:
    kernels/triad.cpp:11:32: note: can't force alignment of ref: *_4
    kernels/triad.cpp:11:32: note: vect_compute_data_ref_alignment:
    kernels/triad.cpp:11:32: note: can't force alignment of ref: *_7
    kernels/triad.cpp:11:32: note: === vect_prune_runtime_alias_test_list ===
    kernels/triad.cpp:11:32: note: improved number of alias checks from 2 to 2
    kernels/triad.cpp:11:32: note: === vect_enhance_data_refs_alignment ===
    kernels/triad.cpp:11:32: note: Unknown misalignment, naturally aligned
    kernels/triad.cpp:11:32: note: Unknown misalignment, naturally aligned
    kernels/triad.cpp:11:32: note: Unknown misalignment, naturally aligned
    kernels/triad.cpp:11:32: note: vect_can_advance_ivs_p:
    kernels/triad.cpp:11:32: note: Analyze phi: l_va_20 = PHI <0(5), l_va_17(6)>
    kernels/triad.cpp:11:32: note: Analyze phi: .MEM_21 = PHI <.MEM_11(D)(5), .MEM_16(6)>
    kernels/triad.cpp:11:32: note: reduc or virtual phi. skip.
    kernels/triad.cpp:11:32: note: vect_model_load_cost: aligned.
    kernels/triad.cpp:11:32: note: vect_get_data_access_cost: inside_cost = 1, outside_cost = 0.
    kernels/triad.cpp:11:32: note: Setting misalignment to unknown (-1).
    kernels/triad.cpp:11:32: note: vect_model_load_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_get_data_access_cost: inside_cost = 2, outside_cost = 0.
    kernels/triad.cpp:11:32: note: Setting misalignment to unknown (-1).
    kernels/triad.cpp:11:32: note: vect_model_store_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_get_data_access_cost: inside_cost = 3, outside_cost = 0.
    kernels/triad.cpp:11:32: note: Setting misalignment to unknown (-1).
    kernels/triad.cpp:11:32: note: vect_model_load_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_get_data_access_cost: inside_cost = 1, outside_cost = 0.
    kernels/triad.cpp:11:32: note: Setting misalignment to unknown (-1).
    kernels/triad.cpp:11:32: note: vect_model_load_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_get_data_access_cost: inside_cost = 2, outside_cost = 0.
    kernels/triad.cpp:11:32: note: vect_model_store_cost: aligned.
    kernels/triad.cpp:11:32: note: vect_get_data_access_cost: inside_cost = 3, outside_cost = 0.
    kernels/triad.cpp:11:32: note: cost model: epilogue peel iters set to vf/2 because loop iterations are unknown .
    kernels/triad.cpp:11:32: note: vect_model_load_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_get_data_access_cost: inside_cost = 1, outside_cost = 0.
    kernels/triad.cpp:11:32: note: vect_model_load_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_get_data_access_cost: inside_cost = 2, outside_cost = 0.
    kernels/triad.cpp:11:32: note: vect_model_store_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_get_data_access_cost: inside_cost = 3, outside_cost = 0.
    kernels/triad.cpp:11:32: note: cost model: epilogue peel iters set to vf/2 because loop iterations are unknown .
    kernels/triad.cpp:11:32: note: Vectorizing an unaligned access.
    kernels/triad.cpp:11:32: note: Vectorizing an unaligned access.
    kernels/triad.cpp:11:32: note: Vectorizing an unaligned access.
    kernels/triad.cpp:11:32: note: === vect_analyze_loop_operations ===
    kernels/triad.cpp:11:32: note: examining phi: l_va_20 = PHI <0(5), l_va_17(6)>
    kernels/triad.cpp:11:32: note: examining phi: .MEM_21 = PHI <.MEM_11(D)(5), .MEM_16(6)>
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG l_va => l_va_20
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: _1 = l_va_20 * 4;
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: _2 = i_a_13(D) + _1;
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: _3 = *_2;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand *_2
    kernels/triad.cpp:11:32: note: not ssa-name.
    kernels/triad.cpp:11:32: note: use not simple.
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand *_2
    kernels/triad.cpp:11:32: note: not ssa-name.
    kernels/triad.cpp:11:32: note: use not simple.
    kernels/triad.cpp:11:32: note: can't use a fully-masked loop because the target doesn't have the appropriate masked load or store.
    kernels/triad.cpp:11:32: note: vect_model_load_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_model_load_cost: inside_cost = 1, prologue_cost = 0 .
    kernels/triad.cpp:11:32: note: ==> examining statement: _4 = i_b_14(D) + _1;
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: _5 = *_4;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand *_4
    kernels/triad.cpp:11:32: note: not ssa-name.
    kernels/triad.cpp:11:32: note: use not simple.
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand *_4
    kernels/triad.cpp:11:32: note: not ssa-name.
    kernels/triad.cpp:11:32: note: use not simple.
    kernels/triad.cpp:11:32: note: vect_model_load_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_model_load_cost: inside_cost = 1, prologue_cost = 0 .
    kernels/triad.cpp:11:32: note: ==> examining statement: _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _5
    kernels/triad.cpp:11:32: note: def_stmt: _5 = *_4;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand 2.0e+0
    kernels/triad.cpp:11:32: note: === vectorizable_operation ===
    kernels/triad.cpp:11:32: note: vect_model_simple_cost: inside_cost = 1, prologue_cost = 1 .
    kernels/triad.cpp:11:32: note: ==> examining statement: _7 = o_c_15(D) + _1;
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _3
    kernels/triad.cpp:11:32: note: def_stmt: _3 = *_2;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _6
    kernels/triad.cpp:11:32: note: def_stmt: _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: === vectorizable_operation ===
    kernels/triad.cpp:11:32: note: vect_model_simple_cost: inside_cost = 1, prologue_cost = 0 .
    kernels/triad.cpp:11:32: note: ==> examining statement: *_7 = _8;
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _8
    kernels/triad.cpp:11:32: note: def_stmt: _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: vect_model_store_cost: unaligned supported by hardware.
    kernels/triad.cpp:11:32: note: vect_model_store_cost: inside_cost = 1, prologue_cost = 0 .
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: l_va_17 = l_va_20 + 1;
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG l_va => l_va_17
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG l_va => l_va_17
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: ==> examining statement: if (i_nValues_12(D) <= l_va_17)
    kernels/triad.cpp:11:32: note: irrelevant.
    kernels/triad.cpp:11:32: note: not using a fully-masked loop.
    cost model: Adding cost of checks for loop versioning aliasing.
    kernels/triad.cpp:11:32: note: cost model: epilogue peel iters set to vf/2 because loop iterations are unknown .
    kernels/triad.cpp:11:32: note: Cost model analysis: 
      Vector inside of loop cost: 5
      Vector prologue cost: 12
      Vector epilogue cost: 12
      Scalar iteration cost: 6
      Scalar outside cost: 1
      Vector outside cost: 24
      prologue iterations: 0
      epilogue iterations: 2
      Calculated minimum iters for profitability: 5
    kernels/triad.cpp:11:32: note:   Runtime profitability threshold = 5
    kernels/triad.cpp:11:32: note:   Static estimate profitability threshold = 5
    kernels/triad.cpp:11:32: note: epilog loop required
    kernels/triad.cpp:11:32: note: vect_can_advance_ivs_p:
    kernels/triad.cpp:11:32: note: Analyze phi: l_va_20 = PHI <0(5), l_va_17(6)>
    kernels/triad.cpp:11:32: note: Analyze phi: .MEM_21 = PHI <.MEM_11(D)(5), .MEM_16(6)>
    kernels/triad.cpp:11:32: note: reduc or virtual phi. skip.
    kernels/triad.cpp:11:32: note: loop vectorized
    kernels/triad.cpp:11:32: note: === vec_transform_loop ===
    kernels/triad.cpp:11:32: note: Profitability threshold is 5 loop iterations.
    split exit edge
    create runtime check for data references *_2 and *_7
    create runtime check for data references *_4 and *_7
    kernels/triad.cpp:11:32: note: created 2 versioning for alias checks.
    kernels/triad.cpp:11:32: note: loop versioned for vectorization because of possible aliasing
    kernels/triad.cpp:11:32: note: vect_update_ivs_after_vectorizer: phi: l_va_20 = PHI <l_va_17(6), 0(12)>
    kernels/triad.cpp:11:32: note: vect_update_ivs_after_vectorizer: phi: .MEM_21 = PHI <.MEM_16(6), .MEM_11(D)(12)>
    kernels/triad.cpp:11:32: note: reduc or virtual phi. skip.
    kernels/triad.cpp:11:32: note: ------>vectorizing phi: l_va_20 = PHI <l_va_17(6), 0(21)>
    kernels/triad.cpp:11:32: note: ------>vectorizing phi: .MEM_21 = PHI <.MEM_16(6), .MEM_11(D)(21)>
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: # DEBUG l_va => l_va_20
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: _1 = l_va_20 * 4;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: _2 = i_a_13(D) + _1;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: _3 = *_2;
    kernels/triad.cpp:11:32: note: transform statement.
    kernels/triad.cpp:11:32: note: transform load. ncopies = 1
    kernels/triad.cpp:11:32: note: create vector_type-pointer variable to type: const vector(4) float  vectorizing a pointer ref: *i_a_13(D)
    kernels/triad.cpp:11:32: note: created i_a_13(D)
    kernels/triad.cpp:11:32: note: add new stmt: vect__3.6_66 = MEM[(const float *)vectp_i_a.4_64];
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: _4 = i_b_14(D) + _1;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: _5 = *_4;
    kernels/triad.cpp:11:32: note: transform statement.
    kernels/triad.cpp:11:32: note: transform load. ncopies = 1
    kernels/triad.cpp:11:32: note: create vector_type-pointer variable to type: const vector(4) float  vectorizing a pointer ref: *i_b_14(D)
    kernels/triad.cpp:11:32: note: created i_b_14(D)
    kernels/triad.cpp:11:32: note: add new stmt: vect__5.9_69 = MEM[(const float *)vectp_i_b.7_67];
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: transform statement.
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _5
    kernels/triad.cpp:11:32: note: def_stmt: _5 = *_4;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand 2.0e+0
    kernels/triad.cpp:11:32: note: transform binary/unary operation.
    kernels/triad.cpp:11:32: note: vect_get_vec_def_for_operand: _5
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _5
    kernels/triad.cpp:11:32: note: def_stmt: _5 = *_4;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note:   def_stmt =  _5 = *_4;
    kernels/triad.cpp:11:32: note: vect_get_vec_def_for_operand: 2.0e+0
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand 2.0e+0
    kernels/triad.cpp:11:32: note: created new init_stmt: vect_cst__70 = { 2.0e+0, 2.0e+0, 2.0e+0, 2.0e+0 };
    kernels/triad.cpp:11:32: note: add new stmt: vect__6.10_71 = vect__5.9_69 * vect_cst__70;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: _7 = o_c_15(D) + _1;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: transform statement.
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _3
    kernels/triad.cpp:11:32: note: def_stmt: _3 = *_2;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _6
    kernels/triad.cpp:11:32: note: def_stmt: _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: transform binary/unary operation.
    kernels/triad.cpp:11:32: note: vect_get_vec_def_for_operand: _3
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _3
    kernels/triad.cpp:11:32: note: def_stmt: _3 = *_2;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note:   def_stmt =  _3 = *_2;
    kernels/triad.cpp:11:32: note: vect_get_vec_def_for_operand: _6
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _6
    kernels/triad.cpp:11:32: note: def_stmt: _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note:   def_stmt =  _6 = _5 * 2.0e+0;
    kernels/triad.cpp:11:32: note: add new stmt: vect__8.11_72 = vect__3.6_66 + vect__6.10_71;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: *_7 = _8;
    kernels/triad.cpp:11:32: note: transform statement.
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _8
    kernels/triad.cpp:11:32: note: def_stmt: _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note: transform store. ncopies = 1
    kernels/triad.cpp:11:32: note: vect_get_vec_def_for_operand: _8
    kernels/triad.cpp:11:32: note: vect_is_simple_use: operand _8
    kernels/triad.cpp:11:32: note: def_stmt: _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: type of def: internal
    kernels/triad.cpp:11:32: note:   def_stmt =  _8 = _3 + _6;
    kernels/triad.cpp:11:32: note: create vector_type-pointer variable to type: vector(4) float  vectorizing a pointer ref: *o_c_15(D)
    kernels/triad.cpp:11:32: note: created o_c_15(D)
    kernels/triad.cpp:11:32: note: add new stmt: MEM[(float *)vectp_o_c.12_73] = vect__8.11_72;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: l_va_17 = l_va_20 + 1;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: # DEBUG l_va => l_va_17
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: # DEBUG l_va => l_va_17
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: # DEBUG BEGIN_STMT
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: vectp_i_a.4_65 = vectp_i_a.4_64 + 16;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: vectp_i_b.7_68 = vectp_i_b.7_67 + 16;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: vectp_o_c.12_74 = vectp_o_c.12_73 + 16;
    kernels/triad.cpp:11:32: note: ------>vectorizing statement: if (i_nValues_12(D) <= l_va_17)
    kernels/triad.cpp:11:32: note: New loop exit condition: if (ivtmp_77 >= bnd.1_61)
    kernels/triad.cpp:11:32: note: LOOP VECTORIZED

    kernels/triad.cpp:7:6: note: vectorized 1 loops in function.
    kernels/triad.cpp:7:6: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:11:32: note: not vectorized: not enough data-refs in basic block.
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:11:32: note: not vectorized: not enough data-refs in basic block.
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:11:32: note: not vectorized: not enough data-refs in basic block.
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:12:15: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:12:15: note: not vectorized: no vectype for stmt: vect__3.6_66 = MEM[(const float *)vectp_i_a.4_64];
    scalar_type: const vector(4) float
    kernels/triad.cpp:12:15: note: not vectorized: no vectype for stmt: vect__5.9_69 = MEM[(const float *)vectp_i_b.7_67];
    scalar_type: const vector(4) float
    kernels/triad.cpp:12:15: note: not vectorized: no vectype for stmt: MEM[(float *)vectp_o_c.12_73] = vect__8.11_72;
    scalar_type: vector(4) float
    kernels/triad.cpp:12:15: note: === vect_analyze_data_ref_accesses ===
    kernels/triad.cpp:12:15: note: not vectorized: no grouped stores in basic block.
    kernels/triad.cpp:12:15: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:12:15: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:12:15: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:12:15: note: not vectorized: not enough data-refs in basic block.
    kernels/triad.cpp:12:15: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:12:15: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:11:32: note: got vectype for stmt: _52 = *_51;
    const vector(4) float
    kernels/triad.cpp:11:32: note: got vectype for stmt: _54 = *_53;
    const vector(4) float
    kernels/triad.cpp:11:32: note: got vectype for stmt: *_56 = _57;
    vector(4) float
    kernels/triad.cpp:11:32: note: === vect_analyze_data_ref_accesses ===
    kernels/triad.cpp:11:32: note: not consecutive access _52 = *_51;
    kernels/triad.cpp:11:32: note: not consecutive access _54 = *_53;
    kernels/triad.cpp:11:32: note: not consecutive access *_56 = _57;
    kernels/triad.cpp:11:32: note: not vectorized: no grouped stores in basic block.
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:11:32: note: got vectype for stmt: _39 = *_38;
    const vector(4) float
    kernels/triad.cpp:11:32: note: got vectype for stmt: _41 = *_40;
    const vector(4) float
    kernels/triad.cpp:11:32: note: got vectype for stmt: *_43 = _44;
    vector(4) float
    kernels/triad.cpp:11:32: note: === vect_analyze_data_ref_accesses ===
    kernels/triad.cpp:11:32: note: not consecutive access _39 = *_38;
    kernels/triad.cpp:11:32: note: not consecutive access _41 = *_40;
    kernels/triad.cpp:11:32: note: not consecutive access *_43 = _44;
    kernels/triad.cpp:11:32: note: not vectorized: no grouped stores in basic block.
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:11:32: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:14:1: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:14:1: note: not vectorized: not enough data-refs in basic block.

    Analyzing loop at kernels/triad.cpp:29
    kernels/triad.cpp:29:5: note: ===== analyze_loop_nest =====
    kernels/triad.cpp:29:5: note: === vect_analyze_loop_form ===
    kernels/triad.cpp:29:5: note: not vectorized: multiple exits.
    kernels/triad.cpp:29:5: note: bad loop form.
    kernels/triad.cpp:16:6: note: vectorized 0 loops in function.
    kernels/triad.cpp:16:6: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:25:5: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:25:5: note: not vectorized: not enough data-refs in basic block.
    kernels/triad.cpp:25:5: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:25:5: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:29:15: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:29:15: note: got vectype for stmt: _1 = *i_a_8(D);
    const vector(4) float
    kernels/triad.cpp:29:15: note: got vectype for stmt: _2 = *i_b_9(D);
    const vector(4) float
    kernels/triad.cpp:29:15: note: got vectype for stmt: *o_c_10(D) = _4;
    vector(4) float
    kernels/triad.cpp:29:15: note: === vect_analyze_data_ref_accesses ===
    kernels/triad.cpp:29:15: note: not consecutive access _1 = *i_a_8(D);
    kernels/triad.cpp:29:15: note: not consecutive access _2 = *i_b_9(D);
    kernels/triad.cpp:29:15: note: not consecutive access *o_c_10(D) = _4;
    kernels/triad.cpp:29:15: note: not vectorized: no grouped stores in basic block.
    kernels/triad.cpp:29:15: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:29:15: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:33:1: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:33:1: note: not vectorized: not enough data-refs in basic block.
    kernels/triad.cpp:33:1: note: ===vect_slp_analyze_bb===
    kernels/triad.cpp:33:1: note: === vect_analyze_data_refs ===
    kernels/triad.cpp:33:1: note: not vectorized: not enough data-refs in basic block.
    g++ -g -pedantic -Wall -Wextra -Werror -O2 -fopenmp driver.cpp ./build/kernels/triad.o -o ./build/auto_vec

## 11.2.2 Vectorization report clang++

    [hgf_rlx5119@ftp-a64n1 Exercise_11]$ make gemm_asm_sve CXX=clang++
    clang++ -g -pedantic -Wall -Wextra -Werror -O2 -fopenmp -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize -c kernels/triad.cpp -o ./build/kernels/triad.o
    kernels/triad.cpp:11:3: remark: vectorized loop (vectorization width: 4, interleaved count: 2) [-Rpass=loop-vectorize]
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      ^
    kernels/triad.cpp:25:8: remark: loop not vectorized: loop control flow is not understood by vectorizer [-Rpass-analysis=loop-vectorize]
        if(l_va <i_nValues){
          ^
    kernels/triad.cpp:25:8: remark: loop not vectorized: loop control flow is not understood by vectorizer [-Rpass-analysis=loop-vectorize]
    kernels/triad.cpp:25:8: remark: loop not vectorized: loop induction variable could not be identified [-Rpass-analysis=loop-vectorize]
    kernels/triad.cpp:25:8: remark: loop not vectorized: loop control flow is not understood by analyzer [-Rpass-analysis=loop-vectorize]
    kernels/triad.cpp:25:8: remark: loop not vectorized [-Rpass-missed=loop-vectorize]
    kernels/triad.cpp:39:3: remark: vectorized loop (vectorization width: 4, interleaved count: 2) [-Rpass=loop-vectorize]
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      ^
    clang++ -g -pedantic -Wall -Wextra -Werror -O2 -fopenmp driver.cpp ./build/kernels/triad.o -o ./build/auto_vec

## 11.2.3 Object dump of g++ 

    [hgf_rlx5119@ftp-a64n1 Exercise_11]$ objdump -S --disassemble build/kernels/triad.o 

    build/kernels/triad.o:     file format elf64-littleaarch64


    Disassembly of section .text:

    0000000000000000 <_Z15multiply_by_twof>:
    #include "triad.h"

    float multiply_by_two(float i_a){
      return 2.0f * i_a;
    }
      0:   1e202800        fadd    s0, s0, s0
      4:   d65f03c0        ret

    0000000000000008 <_Z12triad_simplemPKfS0_Pf>:

    void triad_simple( uint64_t         i_nValues,
                      float    const * i_a,
                      float    const * i_b,
                      float          * o_c ) {
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      8:   b40004a0        cbz     x0, 9c <_Z12triad_simplemPKfS0_Pf+0x94>
      c:   91004025        add     x5, x1, #0x10
      10:   91004064        add     x4, x3, #0x10
      14:   eb05007f        cmp     x3, x5
      18:   d1000406        sub     x6, x0, #0x1
      1c:   fa443022        ccmp    x1, x4, #0x2, cc  // cc = lo, ul, last
      20:   91004045        add     x5, x2, #0x10
      24:   fa4328c0        ccmp    x6, #0x3, #0x0, cs  // cs = hs, nlast
      28:   1a9f97e6        cset    w6, hi  // hi = pmore
      2c:   eb05007f        cmp     x3, x5
      30:   fa443042        ccmp    x2, x4, #0x2, cc  // cc = lo, ul, last
      34:   1a9f37e4        cset    w4, cs  // cs = hs, nlast
      38:   6a0400df        tst     w6, w4
      3c:   54000320        b.eq    a0 <_Z12triad_simplemPKfS0_Pf+0x98>  // b.none
      40:   d342fc05        lsr     x5, x0, #2
      44:   d2800004        mov     x4, #0x0                        // #0
        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      48:   4f00f402        fmov    v2.4s, #2.000000000000000000e+00
      4c:   d37ceca5        lsl     x5, x5, #4
      50:   3ce46841        ldr     q1, [x2, x4]
      54:   3ce46820        ldr     q0, [x1, x4]
      58:   4e22cc20        fmla    v0.4s, v1.4s, v2.4s
      5c:   3ca46860        str     q0, [x3, x4]
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      60:   91004084        add     x4, x4, #0x10
      64:   eb0400bf        cmp     x5, x4
      68:   54ffff41        b.ne    50 <_Z12triad_simplemPKfS0_Pf+0x48>  // b.any
      6c:   927ef404        and     x4, x0, #0xfffffffffffffffc
      70:   eb04001f        cmp     x0, x4
      74:   54000140        b.eq    9c <_Z12triad_simplemPKfS0_Pf+0x94>  // b.none
        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      78:   1e201002        fmov    s2, #2.000000000000000000e+00
      7c:   d503201f        nop
      80:   bc647840        ldr     s0, [x2, x4, lsl #2]
      84:   bc647821        ldr     s1, [x1, x4, lsl #2]
      88:   1f020400        fmadd   s0, s0, s2, s1
      8c:   bc247860        str     s0, [x3, x4, lsl #2]
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      90:   91000484        add     x4, x4, #0x1
      94:   eb04001f        cmp     x0, x4
      98:   54ffff48        b.hi    80 <_Z12triad_simplemPKfS0_Pf+0x78>  // b.pmore
      }
    }
      9c:   d65f03c0        ret
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      a0:   d2800004        mov     x4, #0x0                        // #0
        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      a4:   1e201002        fmov    s2, #2.000000000000000000e+00
      a8:   bc647840        ldr     s0, [x2, x4, lsl #2]
      ac:   bc647821        ldr     s1, [x1, x4, lsl #2]
      b0:   1f020400        fmadd   s0, s0, s2, s1
      b4:   bc247860        str     s0, [x3, x4, lsl #2]
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      b8:   91000484        add     x4, x4, #0x1
      bc:   eb04001f        cmp     x0, x4
      c0:   54ffff41        b.ne    a8 <_Z12triad_simplemPKfS0_Pf+0xa0>  // b.any
    }
      c4:   d65f03c0        ret

    00000000000000c8 <_Z17triad_uncountablemPKfS0_Pf>:
      
      uint64_t l_va = 0;

      while(true){

        if(l_va <i_nValues){
      c8:   b50000e0        cbnz    x0, e4 <_Z17triad_uncountablemPKfS0_Pf+0x1c>
          break;
        }

        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      cc:   1e201002        fmov    s2, #2.000000000000000000e+00
      d0:   bd400040        ldr     s0, [x2]
      d4:   bd400021        ldr     s1, [x1]
      d8:   1f020400        fmadd   s0, s0, s2, s1
      dc:   bd000060        str     s0, [x3]
        if(l_va <i_nValues){
      e0:   17fffffc        b       d0 <_Z17triad_uncountablemPKfS0_Pf+0x8>

      }

    }
      e4:   d65f03c0        ret

    00000000000000e8 <_Z22triad_with_extern_funcmPKfS0_Pf>:
      e8:   14000000        b       8 <_Z12triad_simplemPKfS0_Pf>

## 11.2.4 Objdump of file compiled with clang++

    [hgf_rlx5119@ftp-a64n1 Exercise_11]$ objdump -S --disassemble build/kernels/triad.o 

    build/kernels/triad.o:     file format elf64-littleaarch64


    Disassembly of section .text:

    0000000000000000 <_Z15multiply_by_twof>:
    #include "triad.h"

    float multiply_by_two(float i_a){
      return 2.0f * i_a;
      0:   1e202800        fadd    s0, s0, s0
      4:   d65f03c0        ret

    0000000000000008 <_Z12triad_simplemPKfS0_Pf>:

    void triad_simple( uint64_t         i_nValues,
                      float    const * i_a,
                      float    const * i_b,
                      float          * o_c ) {
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      8:   b40006a0        cbz     x0, dc <_Z12triad_simplemPKfS0_Pf+0xd4>
      c:   f1001c1f        cmp     x0, #0x7
      10:   54000068        b.hi    1c <_Z12triad_simplemPKfS0_Pf+0x14>  // b.pmore
      14:   aa1f03e8        mov     x8, xzr
      18:   14000025        b       ac <_Z12triad_simplemPKfS0_Pf+0xa4>
      1c:   d37ef409        lsl     x9, x0, #2
      20:   8b09002b        add     x11, x1, x9
      24:   8b09006a        add     x10, x3, x9
      28:   eb03017f        cmp     x11, x3
      2c:   8b090049        add     x9, x2, x9
      30:   1a9f97eb        cset    w11, hi  // hi = pmore
      34:   eb01015f        cmp     x10, x1
      38:   1a9f97ec        cset    w12, hi  // hi = pmore
      3c:   eb03013f        cmp     x9, x3
      40:   1a9f97e9        cset    w9, hi  // hi = pmore
      44:   eb02015f        cmp     x10, x2
      48:   aa1f03e8        mov     x8, xzr
      4c:   0a0c016b        and     w11, w11, w12
      50:   1a9f97ea        cset    w10, hi  // hi = pmore
      54:   370002cb        tbnz    w11, #0, ac <_Z12triad_simplemPKfS0_Pf+0xa4>
      58:   0a0a0129        and     w9, w9, w10
      5c:   37000289        tbnz    w9, #0, ac <_Z12triad_simplemPKfS0_Pf+0xa4>
      60:   927df008        and     x8, x0, #0xfffffffffffffff8
      64:   91004029        add     x9, x1, #0x10
      68:   9100404a        add     x10, x2, #0x10
      6c:   9100406b        add     x11, x3, #0x10
      70:   aa0803ec        mov     x12, x8
        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      74:   ad7f8d42        ldp     q2, q3, [x10, #-16]
      78:   ad7f8520        ldp     q0, q1, [x9, #-16]
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      7c:   91008129        add     x9, x9, #0x20
      80:   9100814a        add     x10, x10, #0x20
        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      84:   4e22d442        fadd    v2.4s, v2.4s, v2.4s
      88:   4e23d463        fadd    v3.4s, v3.4s, v3.4s
      8c:   4e22d400        fadd    v0.4s, v0.4s, v2.4s
      90:   4e23d421        fadd    v1.4s, v1.4s, v3.4s
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      94:   f100218c        subs    x12, x12, #0x8
        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      98:   ad3f8560        stp     q0, q1, [x11, #-16]
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      9c:   9100816b        add     x11, x11, #0x20
      a0:   54fffea1        b.ne    74 <_Z12triad_simplemPKfS0_Pf+0x6c>  // b.any
      a4:   eb00011f        cmp     x8, x0
      a8:   540001a0        b.eq    dc <_Z12triad_simplemPKfS0_Pf+0xd4>  // b.none
      ac:   d37ef50b        lsl     x11, x8, #2
      b0:   cb080009        sub     x9, x0, x8
      b4:   8b0b0068        add     x8, x3, x11
      b8:   8b0b004a        add     x10, x2, x11
      bc:   8b0b002b        add     x11, x1, x11
        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      c0:   bc404560        ldr     s0, [x11], #4
      c4:   bc404541        ldr     s1, [x10], #4
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      c8:   f1000529        subs    x9, x9, #0x1
        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      cc:   1e212821        fadd    s1, s1, s1
      d0:   1e212800        fadd    s0, s0, s1
      d4:   bc004500        str     s0, [x8], #4
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
      d8:   54ffff41        b.ne    c0 <_Z12triad_simplemPKfS0_Pf+0xb8>  // b.any
      }
    }
      dc:   d65f03c0        ret

    00000000000000e0 <_Z17triad_uncountablemPKfS0_Pf>:
      
      uint64_t l_va = 0;

      while(true){

        if(l_va <i_nValues){
      e0:   b4000040        cbz     x0, e8 <_Z17triad_uncountablemPKfS0_Pf+0x8>

        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];

      }

    }
      e4:   d65f03c0        ret
        o_c[l_va] = i_a[l_va] + 2.0f * i_b[l_va];
      e8:   bd400040        ldr     s0, [x2]
      ec:   bd400021        ldr     s1, [x1]
      f0:   1e202800        fadd    s0, s0, s0
      f4:   1e202820        fadd    s0, s1, s0
      f8:   bd000060        str     s0, [x3]
        if(l_va <i_nValues){
      fc:   17fffffb        b       e8 <_Z17triad_uncountablemPKfS0_Pf+0x8>

    0000000000000100 <_Z22triad_with_extern_funcmPKfS0_Pf>:

    void triad_with_extern_func( uint64_t         i_nValues,
                            float    const * i_a,
                            float    const * i_b,
                            float          * o_c ){
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    100:   b40006a0        cbz     x0, 1d4 <_Z22triad_with_extern_funcmPKfS0_Pf+0xd4>
    104:   f1001c1f        cmp     x0, #0x7
    108:   54000068        b.hi    114 <_Z22triad_with_extern_funcmPKfS0_Pf+0x14>  // b.pmore
    10c:   aa1f03e8        mov     x8, xzr
    110:   14000025        b       1a4 <_Z22triad_with_extern_funcmPKfS0_Pf+0xa4>
    114:   d37ef409        lsl     x9, x0, #2
    118:   8b09002b        add     x11, x1, x9
    11c:   8b09006a        add     x10, x3, x9
    120:   eb03017f        cmp     x11, x3
    124:   8b090049        add     x9, x2, x9
    128:   1a9f97eb        cset    w11, hi  // hi = pmore
    12c:   eb01015f        cmp     x10, x1
    130:   1a9f97ec        cset    w12, hi  // hi = pmore
    134:   eb03013f        cmp     x9, x3
    138:   1a9f97e9        cset    w9, hi  // hi = pmore
    13c:   eb02015f        cmp     x10, x2
    140:   aa1f03e8        mov     x8, xzr
    144:   0a0c016b        and     w11, w11, w12
    148:   1a9f97ea        cset    w10, hi  // hi = pmore
    14c:   370002cb        tbnz    w11, #0, 1a4 <_Z22triad_with_extern_funcmPKfS0_Pf+0xa4>
    150:   0a0a0129        and     w9, w9, w10
    154:   37000289        tbnz    w9, #0, 1a4 <_Z22triad_with_extern_funcmPKfS0_Pf+0xa4>
    158:   927df008        and     x8, x0, #0xfffffffffffffff8
    15c:   91004029        add     x9, x1, #0x10
    160:   9100404a        add     x10, x2, #0x10
    164:   9100406b        add     x11, x3, #0x10
    168:   aa0803ec        mov     x12, x8
        o_c[l_va] = i_a[l_va] + multiply_by_two(i_b[l_va]);
    16c:   ad7f8d42        ldp     q2, q3, [x10, #-16]
    170:   ad7f8520        ldp     q0, q1, [x9, #-16]
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    174:   91008129        add     x9, x9, #0x20
    178:   9100814a        add     x10, x10, #0x20
      return 2.0f * i_a;
    17c:   4e22d442        fadd    v2.4s, v2.4s, v2.4s
    180:   4e23d463        fadd    v3.4s, v3.4s, v3.4s
        o_c[l_va] = i_a[l_va] + multiply_by_two(i_b[l_va]);
    184:   4e22d400        fadd    v0.4s, v0.4s, v2.4s
    188:   4e23d421        fadd    v1.4s, v1.4s, v3.4s
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    18c:   f100218c        subs    x12, x12, #0x8
        o_c[l_va] = i_a[l_va] + multiply_by_two(i_b[l_va]);
    190:   ad3f8560        stp     q0, q1, [x11, #-16]
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    194:   9100816b        add     x11, x11, #0x20
    198:   54fffea1        b.ne    16c <_Z22triad_with_extern_funcmPKfS0_Pf+0x6c>  // b.any
    19c:   eb00011f        cmp     x8, x0
    1a0:   540001a0        b.eq    1d4 <_Z22triad_with_extern_funcmPKfS0_Pf+0xd4>  // b.none
    1a4:   d37ef50b        lsl     x11, x8, #2
    1a8:   cb080009        sub     x9, x0, x8
    1ac:   8b0b0068        add     x8, x3, x11
    1b0:   8b0b004a        add     x10, x2, x11
    1b4:   8b0b002b        add     x11, x1, x11
        o_c[l_va] = i_a[l_va] + multiply_by_two(i_b[l_va]);
    1b8:   bc404560        ldr     s0, [x11], #4
    1bc:   bc404541        ldr     s1, [x10], #4
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    1c0:   f1000529        subs    x9, x9, #0x1
      return 2.0f * i_a;
    1c4:   1e212821        fadd    s1, s1, s1
        o_c[l_va] = i_a[l_va] + multiply_by_two(i_b[l_va]);
    1c8:   1e212800        fadd    s0, s0, s1
    1cc:   bc004500        str     s0, [x8], #4
      for( uint64_t l_va = 0; l_va < i_nValues; l_va++ ) {
    1d0:   54ffff41        b.ne    1b8 <_Z22triad_with_extern_funcmPKfS0_Pf+0xb8>  // b.any
      }
    1d4:   d65f03c0        ret

# 11.3 Verifying optimization levels
Performance with o2 performance level is shown in 11.4.*. External function call is very bad for performance. Countable loop and uncountable loop perform almost the same.
## 11.3.1 clang++ without optimization

    [hgf_rlx5119@ftp-a64n1 Exercise_11]$ ./build/auto_vec 1024 10000000
    working with:
      N_VALUES: 1024; this means 0.00390625 MiB per array
      N_REPEATS: 10000000
    benchmarking triad_simple
      performance:
        duration: 82.7053 seconds
        GFLOPS: 0.247626
        GiB/s: 1.38372
    benchmarking triad_uncountable
      performance:
        duration: 81.4883 seconds
        GFLOPS: 0.251324
        GiB/s: 1.40438
    benchmarking triad_with_extern_func
      performance:
        duration: 130.997 seconds
        GFLOPS: 0.15634
        GiB/s: 0.873617

## 11.3.2 g++ without optimization

    [hgf_rlx5119@ftp-a64n1 Exercise_11]$ ./build/auto_vec 1024 10000000
    working with:
      N_VALUES: 1024; this means 0.00390625 MiB per array
      N_REPEATS: 10000000
    benchmarking triad_simple
      performance:
        duration: 89.4374 seconds
        GFLOPS: 0.228987
        GiB/s: 1.27956
    benchmarking triad_uncountable
      performance:
        duration: 89.8725 seconds
        GFLOPS: 0.227878
        GiB/s: 1.27337
    benchmarking triad_with_extern_func
      performance:
        duration: 129.388 seconds
        GFLOPS: 0.158284
        GiB/s: 0.88448



# 11.4 Impact of auto-vectorization 

Obviously a lot faster than without optimization. 

## 11.4.1 Using clang++ 

The following run was done using the -02 

    [hgf_rlx5119@ftp-a64n1 Exercise_11]$ ./build/auto_vec 1024 10000000
  working with:
    N_VALUES: 1024; this means 0.00390625 MiB per array
    N_REPEATS: 10000000
  benchmarking triad_simple
    performance:
      duration: 4.58082 seconds
      GFLOPS: 4.47082
      GiB/s: 24.9826
  benchmarking triad_uncountable
    performance:
      duration: 22.7804 seconds
      GFLOPS: 0.899017
      GiB/s: 5.02365
  benchmarking triad_with_extern_func
    performance:
      duration: 22.7224 seconds
      GFLOPS: 0.901314
      GiB/s: 5.03648

# 11.4.2 Using g++
    [hgf_rlx5119@ftp-a64n1 Exercise_11]$ ./build/auto_vec 1024 10000000
    working with:
      N_VALUES: 1024; this means 0.00390625 MiB per array
      N_REPEATS: 10000000
    benchmarking triad_simple
      performance:
        duration: 4.73176 seconds
        GFLOPS: 4.3282
        GiB/s: 24.1857
    benchmarking triad_uncountable
      performance:
        duration: 19.3316 seconds
        GFLOPS: 1.0594
        GiB/s: 5.91988
    benchmarking triad_with_extern_func
      performance:
        duration: 19.3676 seconds
        GFLOPS: 1.05744
        GiB/s: 5.90889



# 11.5 Breaking the vectorization
To break auto-vectorization, three new functions are introduced. 
- multiply_by_two: just a simple extern function to break vectorization
- triad_uncountable: introducing a while loop with weird control flow, just infinite while with break was not enough. two exits had to be made
- triad_with_extern_func: using extern func to break vectorization

triad_uncountable leads to unvectorized code with both g++ and clang++. But triad_with_extern_func is still vectorized by clang++, had to make extern func more complex. The results produced by the disassembler can be seen in 11.2. Performance is shown in 11.4.



