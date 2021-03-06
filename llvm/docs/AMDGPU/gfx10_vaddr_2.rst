..
    **************************************************
    *                                                *
    *   Automatically generated file, do not edit!   *
    *                                                *
    **************************************************

.. _amdgpu_synid_gfx10_vaddr_2:

vaddr
=====

A 64-bit flat global address or a 32-bit offset depending on addressing mode:

* Address = :ref:`vaddr<amdgpu_synid_gfx10_vaddr_2>` + :ref:`offset12s<amdgpu_synid_flat_offset12s>`. :ref:`vaddr<amdgpu_synid_gfx10_vaddr_2>` is a 64-bit address. This mode is indicated by :ref:`saddr<amdgpu_synid_gfx10_saddr>` set to :ref:`off<amdgpu_synid_off>`.
* Address = :ref:`saddr<amdgpu_synid_gfx10_saddr>` + :ref:`vaddr<amdgpu_synid_gfx10_vaddr_2>` + :ref:`offset12s<amdgpu_synid_flat_offset12s>`. :ref:`vaddr<amdgpu_synid_gfx10_vaddr_2>` is a 32-bit offset. This mode is used when :ref:`saddr<amdgpu_synid_gfx10_saddr>` is not :ref:`off<amdgpu_synid_off>`.

*Size:* 1 or 2 dwords.

*Operands:* :ref:`v<amdgpu_synid_v>`
