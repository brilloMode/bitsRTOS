.section .text
.global rtx_context_switch
rtx_context_switch:
    push {r0-r12, lr}
    # ... (full save/restore)
    pop {r0-r12, pc}
    