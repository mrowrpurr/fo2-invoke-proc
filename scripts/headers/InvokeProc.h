/*
    Crazy DSL for invoking functions by name.

    Why?

        1. The default provided syntax in Fallout 2 is weird:

            variable proc = "name_of_proc";
            proc(123);

        2. The sfall compiler optimizer (which you should use)
           makes this very challenging because it needs to
           know that you're calling the given procedure.

           If you don't call the procedure *or* if you do not
           use the return result of the procedure, then the 
           optimizer will not include the procedure in the
           compiled output. So you cannot call it!

        3. I want to call procedures by name *and* provide
           arguments (you cannot provide arguments using SignalNamed).

        4. Whatever, it's fun!

    How?

        - A bunch of trickery and tomfoolery using macros.

    Usage?

        Note: supports up to 9 procedure arguments by default.

              If you need more, edit the header or copy/paste
              its defines to create ones for more arguments.

        procedure call_me0 begin
            display_msg("You called 'call_me');
            return "Some result";
        end

        procedure call_me1(variable x) begin
            display_msg("You called 'call_me' with " + x);
            return "Some result";
        end

        procedure call_me2(variable x, variable y) begin
            display_msg("You called 'call_me' with " + x + " and " + y);
            return "Some result";
        end

        procedure start begin
            if game_loaded then begin

                // You MUST tell the compiler about all of the procs
                // which you plan on calling.
                setup_invoke_procs begin
                    register_invoke_proc call_me0;       // No arguments
                    register_invoke_proc call_me1(0);    // One argument
                    register_invoke_proc call_me1(0, 0); // Two arguments
                end

                // Invoke proc (without getting return result)
                call_invoke_proc1("call_me1", "Some argument value");

                // Invoke proc (and store the result)
                variable result = invoke_proc2("call_me", "arg1 value", "arg2 value");

                // Reminder: if you do not *use* the result,
                //           e.g. with this call to display_msg,
                //           the optimizer won't invoke the proc at all.
                display_msg("Got result: " + result);
            end
        end

    This is madness!
    
        - Yep.

    Who?

        ~ Mrowr Purr ~
*/

// SETUP CODE

// Private ariable used to fool the compiler so it knows
// we want to call certain procedures.
variable __setup_invoke_procs_compiler_trick_variable = true;

// setup_invoke_procs is just a conditional block which *never runs*
// (but the compiler doesn't know that!)
#define setup_invoke_procs \
    __setup_invoke_procs_compiler_trick_variable = false; \
    if __setup_invoke_procs_compiler_trick_variable then

// Semantics to show what we're doing in setup_invoke_procs
#define register_invoke_proc call

// INVOCATION CODE

// Private variables to make it possible to call_invoke_proc
// without using the result & keeping the compiler from
// throwing away the procedure call.
variable __dialogue_currently_calling_proc_compiler_trick_variable = true;
variable __dialogue_currently_calling_proc_result;

// String variable for storing the name of the procedure to be called.
// This is how Fallout 2 allows for dynamic procedure invocation by name.
variable __dialogue_currently_calling_proc_fn_name = "";

#define call_invoke_proc(fn) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

#define call_invoke_proc1(fn, arg) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(arg); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

#define call_invoke_proc2(fn, arg1, arg2) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(arg1, arg2); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

#define call_invoke_proc3(fn, arg1, arg2, arg3) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(arg1, arg2, arg3); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

#define call_invoke_proc4(fn, arg1, arg2, arg3, arg4) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(arg1, arg2, arg3, arg4); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

#define call_invoke_proc5(fn, arg1, arg2, arg3, arg4, arg5) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(arg1, arg2, arg3, arg4, arg5); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

#define call_invoke_proc6(fn, arg1, arg2, arg3, arg4, arg5, arg6) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(arg1, arg2, arg3, arg4, arg5, arg6); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

#define call_invoke_proc7(fn, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(arg1, arg2, arg3, arg4, arg5, arg6, arg7); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

#define call_invoke_proc8(fn, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

#define call_invoke_proc9(fn, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
    __dialogue_currently_calling_proc_fn_name = fn; \
    __dialogue_currently_calling_proc_result = fn(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9); \
    __dialogue_currently_calling_proc_compiler_trick_variable = false; \
    if __dialogue_currently_calling_proc_compiler_trick_variable then debug_msg(__dialogue_currently_calling_proc_result)

procedure invoke_proc(variable fn) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn();
end

procedure invoke_proc1(variable fn, variable arg) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn(arg);
end

procedure invoke_proc2(variable fn, variable arg1, variable arg2) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn(arg1, arg2);
end

procedure invoke_proc3(variable fn, variable arg1, variable arg2, variable arg3) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn(arg1, arg2, arg3);
end

procedure invoke_proc4(variable fn, variable arg1, variable arg2, variable arg3, variable arg4) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn(arg1, arg2, arg3, arg4);
end

procedure invoke_proc5(variable fn, variable arg1, variable arg2, variable arg3, variable arg4, variable arg5) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn(arg1, arg2, arg3, arg4, arg5);
end

procedure invoke_proc6(variable fn, variable arg1, variable arg2, variable arg3, variable arg4, variable arg5, variable arg6) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn(arg1, arg2, arg3, arg4, arg5, arg6);
end

procedure invoke_proc7(variable fn, variable arg1, variable arg2, variable arg3, variable arg4, variable arg5, variable arg6, variable arg7) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
end

procedure invoke_proc8(variable fn, variable arg1, variable arg2, variable arg3, variable arg4, variable arg5, variable arg6, variable arg7, variable arg8) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
end

procedure invoke_proc9(variable fn, variable arg1, variable arg2, variable arg3, variable arg4, variable arg5, variable arg6, variable arg7, variable arg8, variable arg9) begin
    __dialogue_currently_calling_proc_fn_name = fn;
    return fn(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
end

