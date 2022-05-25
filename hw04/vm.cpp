#include "vm.h"

#include <iostream>
#include <limits>

#include "util.h"


namespace vm {


vm_state create_vm(bool debug) {
    vm_state state;

    // enable vm debugging
    state.debug = debug;

    // todo: i might need to fix the argument below
    register_instruction(state, "PRINT", [](const vm_state& vmstate, const item_t /*arg*/) {
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to PRINT: Stack is empty!\n");
            return false;
        }
        std::cout << vmstate.stack.top() << '\n' << std::endl;
        return true;
    });

    register_instruction(state,"LOAD_CONST",[](vm_state& vmstate, const item_t number) -> bool {
        vmstate.stack.push(number);
        return true;
      //todo: anything else?
    });

    register_instruction(state,"EXIT",[](vm_state& vmstate, const item_t ) -> bool {
        //todo: implement
        std::cout << "Exitting... \n";
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to EXIT: Stack is empty!\n");
            return false;
        }
        std::cout << vmstate.stack.top();
        return true;
    });

    register_instruction(state,"POP",[](vm_state& vmstate, const item_t number) -> bool {
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to POP: Stack is empty!\n");
            return false;
        }
        vmstate.stack.pop();
        return true;
    });

    register_instruction(state,"ADD",[](vm_state& vmstate, const item_t number) -> bool {
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to ADD: Stack is empty! Nothing to add.\n");
            return false;
        }
        auto tos = vmstate.stack.top();
        vmstate.stack.pop();
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to ADD: Stack is empty! Missing second argument.\n");
            return false;
        }
        auto tos1 = vmstate.stack.top();
        vmstate.stack.pop();
        vmstate.stack.push(tos1+tos);
        return true;
    });

    register_instruction(state,"DIV",[](vm_state& vmstate, const item_t number) -> bool {
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to DIV: Stack is empty! Nothing to divide. \n");
            return false;
        }
        auto tos = vmstate.stack.top();
        vmstate.stack.pop();
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to DIV: Stack is empty!. Missing second argument. \n");
            return false;
        }
        auto tos1 = vmstate.stack.top();
        vmstate.stack.pop();
        if (tos == 0l ) throw div_by_zero("Division by zero!\n");
        vmstate.stack.push(tos1/tos);
        return true;
    });

    register_instruction(state,"EQ",[](vm_state& vmstate, const item_t number) -> bool {
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to EQ: Stack is empty! Nothing to compare. \n");
            return false;
        }
        auto tos = vmstate.stack.top();
        vmstate.stack.pop();
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to EQ: Stack is empty! Missing second argument. \n");
            return false;
        }
        auto tos1 = vmstate.stack.top();
        vmstate.stack.pop();
        (tos== tos1) ? vmstate.stack.push(1l) : vmstate.stack.push(0l);
        return true;
    });

    register_instruction(state,"NEQ",[](vm_state& vmstate, const item_t number) -> bool {
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to NEQ: Stack is empty! Nothing to compare. \n");
            return false;
        }
        auto tos = vmstate.stack.top();
        vmstate.stack.pop();
        if (vmstate.stack.empty()) {
            throw vm_stackfail("Error on call to NEQ: Stack is empty! Missing second argument. \n");
            return false;
        }
        auto tos1 = vmstate.stack.top();
        vmstate.stack.pop();
        (tos != tos1) ? vmstate.stack.push(1l) : vmstate.stack.push(0l);
        return true;
    });

    register_instruction(state,"DUP",[](vm_state& vmstate, const item_t number) -> bool {
        //todo: implement
        if (vmstate.stack.empty())
        {
            throw vm_stackfail("Error on call to DUP: Stack is empty! Nothing to duplicate. \n");
            return false;
        }
        auto tos = vmstate.stack.top();
        vmstate.stack.push(tos);
        return true;
    });

    register_instruction(state,"JMP",[](vm_state& vmstate, const item_t addr) -> bool {
        //todo: error handling
        if ( static_cast<size_t>(addr) > vmstate.pc_bound)
            throw vm_segfault("Error on call to JMP: Given address is out of bound! \n");
        vmstate.pc = static_cast<size_t>(addr);
        return true;
    });

    register_instruction(state,"JMPZ",[](vm_state& vmstate, const item_t addr) -> bool {
        //todo: error handling
        if (vmstate.stack.empty())
            throw vm_stackfail("Error on call to JMPZ: Stack is empty! Nowhere to jump. \n");
        auto tos = vmstate.stack.top();
        if (tos == 0)
        {
            vmstate.stack.pop();
            if ( static_cast<size_t>(addr) > vmstate.pc_bound)
                throw vm_segfault("Error on call to JMPZ: Given address is out of bound! \n");
            vmstate.pc = static_cast<size_t>(addr);
            return true;
        }
        std::cout << "TOS is not zero!\n";
        return true;
    });

    register_instruction(state,"WRITE",[](vm_state& vmstate, const item_t) -> bool {
        //todo: implement
        if (vmstate.stack.empty())
        {
            throw vm_stackfail("Error on call to WRITE: Stack is empty! Nothing to duplicate. \n");
            return false;
        }
        auto tos = vmstate.stack.top();
        vmstate.outText.append(std::to_string(tos) );
        return true;
    });

    register_instruction(state,"WRITE_CHAR",[](vm_state& vmstate, const item_t ) -> bool {
        //todo: implement
        if (vmstate.stack.empty())
        {
            throw vm_stackfail("Error on call to WRITE_CHAR: Stack is empty! Nothing to duplicate. \n");
            return false;
        }
        auto tos = vmstate.stack.top();
        char a = char(tos);
        std::string s1{};
        s1 =  char(tos);
        vmstate.outText.append(s1);
//        auto str = std::to_string(tos);
//        for (const char& c : str) {
//            vmstate.outText.append( std::to_string((int)c ));
//        }
        //vmstate.outText.append("\n");
        return true;
    });

    // TODO create instructions

    return state;
}


void register_instruction(vm_state& state, std::string_view name,
                          const op_action_t& action) {
    size_t op_id = state.next_op_id;

    // TODO make instruction available to vm
    // todo: Error handling?
    state.instruction_ids[std::string(name)] = op_id;
    state.instruction_names[op_id] = name;
    state.instruction_actions[op_id] = action;
    ++state.next_op_id;
}

// save operations into an std::vector as pairs of (op_id,argument)
code_t assemble(const vm_state& state, std::string_view input_program) {
    code_t code;

    // convert each line separately
    for (auto& line : util::split(input_program, '\n')) {

        auto line_words = util::split(line, ' ');

        // only support instruction and one argument
        if (line_words.size() >= 3) {
            throw invalid_instruction{std::string{"more than one instruction argument: "} + line};
        }

        // look up instruction id
        auto& op_name = line_words[0];
        auto find_op_id = state.instruction_ids.find(op_name);
        if (find_op_id == std::end(state.instruction_ids)) {
            throw invalid_instruction{std::string{"unknown instruction: "} + op_name};
        }
        op_id_t op_id = find_op_id->second;

        // parse the argument
        item_t argument{0};
        if (line_words.size() == 2) {
            argument = std::stoll(line_words[1]);
        }

        // and save the instruction to the code store
        code.emplace_back(op_id, argument);
    }

    return code;
}


std::tuple<item_t, std::string> run(vm_state& vm, const code_t& code) {
    // to help you debugging the code!
    if (vm.debug) {
        std::cout << "=== running vm ======================" << std::endl;
        std::cout << "disassembly of run code:" << std::endl;
        for (const auto &[op_id, arg] : code) {
            if (not vm.instruction_names.contains(op_id)) {
                std::cout << "could not disassemble - op_id unknown..." << std::endl;
                std::cout << "turning off debug mode." << std::endl;
                vm.debug = false;
                break;
            }
            std::cout << vm.instruction_names[op_id] << " " << arg << std::endl;
        }
        std::cout << "=== end of disassembly" << std::endl << std::endl;
    }

    // Set the maximum pc bound for error checking.
    vm.pc_bound = code.size() - 1;

    // execution loop for the machine
    while (true) {

        auto& [op_id, arg] = code[vm.pc];

        if (vm.debug) {
            std::cout << "-- exec " << vm.instruction_names[op_id] << " arg=" << arg << " at pc=" << vm.pc << std::endl;
        }

        // increase the program counter here so its value can be overwritten
        // by the instruction when it executes!
        vm.pc += 1;

        // TODO execute instruction and stop if the action returns false
        auto action {vm.instruction_actions[op_id]};
        if (not action(vm,arg))
            return {1,"An action could not be executed!\n"};
        if (vm.pc == code.size())
            break;
    }

    return {vm.stack.top(), vm.outText }; // TODO: return tuple(exit value, output text)
}


} // namespace vm
