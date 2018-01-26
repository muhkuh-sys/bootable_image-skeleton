# -*- coding: utf-8 -*-
#-------------------------------------------------------------------------#
#   Copyright (C) 2011 by Christoph Thelen                                #
#   doc_bacardi@users.sourceforge.net                                     #
#                                                                         #
#   This program is free software; you can redistribute it and/or modify  #
#   it under the terms of the GNU General Public License as published by  #
#   the Free Software Foundation; either version 2 of the License, or     #
#   (at your option) any later version.                                   #
#                                                                         #
#   This program is distributed in the hope that it will be useful,       #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
#   GNU General Public License for more details.                          #
#                                                                         #
#   You should have received a copy of the GNU General Public License     #
#   along with this program; if not, write to the                         #
#   Free Software Foundation, Inc.,                                       #
#   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             #
#-------------------------------------------------------------------------#


#----------------------------------------------------------------------------
#
# Set up the Muhkuh Build System.
#
SConscript('mbs/SConscript')
Import('atEnv')

# Create a build environment for the ARM9 based netX chips.
env_arm9 = atEnv.DEFAULT.CreateEnvironment(['gcc-arm-none-eabi-4.7', 'asciidoc'])

# TODO: Comment out the next line if you do not want a netX500 / netX100 build.
env_arm9.CreateCompilerEnv('NETX500', ['arch=armv5te'])

# TODO: Comment out the next line if you do not want a netX51 / netX52 build.
env_arm9.CreateCompilerEnv('NETX56', ['arch=armv5te'])

# TODO: Comment out the next line if you do not want a netX50 build.
env_arm9.CreateCompilerEnv('NETX50', ['arch=armv5te'])

# TODO: Comment out the next line if you do not want a netX10 build.
env_arm9.CreateCompilerEnv('NETX10', ['arch=armv5te'])

# Create a build environment for the Cortex-R7 and Cortex-A9 based netX chips.
env_cortexR7 = atEnv.DEFAULT.CreateEnvironment(['gcc-arm-none-eabi-4.9', 'asciidoc'])

# TODO: Comment out the next line if you do not want a netX4000 RELAXED build.
env_cortexR7.CreateCompilerEnv('NETX4000_RELAXED', ['arch=armv7', 'thumb'], ['arch=armv7-r', 'thumb'])

# Create a build environment for the Cortex-M4 based netX chips.
env_cortexM4 = atEnv.DEFAULT.CreateEnvironment(['gcc-arm-none-eabi-4.9', 'asciidoc'])

# TODO: Comment out the next line if you do not want a netX90 MPW build.
env_cortexM4.CreateCompilerEnv('NETX90_MPW', ['arch=armv7', 'thumb'], ['arch=armv7e-m', 'thumb'])

# TODO: Comment out the next line if you do not want a netX90 MPW APP build.
env_cortexM4.CreateCompilerEnv('NETX90_MPW_APP', ['arch=armv7', 'thumb'], ['arch=armv7e-m', 'thumb'])


#----------------------------------------------------------------------------
#
# Build the platform libraries.
#
SConscript('platform/SConscript')


#----------------------------------------------------------------------------
#
# Get the source code version from the VCS.
#
atEnv.DEFAULT.Version('#targets/version/version.h', 'templates/version.h')


#----------------------------------------------------------------------------
# This is the list of sources. The elements must be separated with whitespace
# (i.e. spaces, tabs, newlines). The amount of whitespace does not matter.
sources = """
	src/header.c
	src/init.S
	src/main.c
"""

sources_netx90_app_additional = """
	src/netx90_app/app_hboot_header_iflash.c
	src/netx90_app/cm4_app_vector_table_iflash.c
"""

#----------------------------------------------------------------------------
#
# Build all files.
#

# The list of include folders. Here it is used for all files.
astrIncludePaths = ['src', '#platform/src', '#platform/src/lib', '#targets/version']

# netX4000 RELAXED COM CPU
if hasattr(atEnv, 'NETX4000_RELAXED') == True:
    env_netx4000_relaxed_com = atEnv.NETX4000_RELAXED.Clone()
    env_netx4000_relaxed_com.Append(CPPPATH = astrIncludePaths)
    env_netx4000_relaxed_com.Replace(LDFILE = 'src/netx4000/netx4000_cr7_intram.ld')
    src_netx4000_relaxed_com = env_netx4000_relaxed_com.SetBuildPath('targets/netx4000_relaxed_com', 'src', sources)
    elf_netx4000_relaxed_com = env_netx4000_relaxed_com.Elf('targets/netx4000_relaxed_com/netx4000_relaxed_com.elf', src_netx4000_relaxed_com + env_netx4000_relaxed_com['PLATFORM_LIBRARY'])
    txt_netx4000_relaxed_com = env_netx4000_relaxed_com.ObjDump('targets/netx4000_relaxed_com/netx4000_relaxed_com.txt', elf_netx4000_relaxed_com, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])

if hasattr(atEnv, 'NETX500') == True:
    env_netx500 = atEnv.NETX500.Clone()
    env_netx500.Append(CPPPATH = astrIncludePaths)
    env_netx500.Replace(LDFILE = 'src/netx500/netx500_intram.ld')
    src_netx500 = env_netx500.SetBuildPath('targets/netx500', 'src', sources)
    elf_netx500 = env_netx500.Elf('targets/netx500/netx500.elf', src_netx500 + env_netx500['PLATFORM_LIBRARY'])
    bb0_netx500 = env_netx500.BootBlock('targets/netx500/netx.rom', elf_netx500, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
    bb1_netx500 = env_netx500.BootBlock('targets/netx500/netx500_spi_intram.bin', elf_netx500, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

if hasattr(atEnv, 'NETX90_MPW') == True:
    # Blinki for the netX90 communication CPU.
    env_netx90_mpw_com = atEnv.NETX90_MPW.Clone()
    env_netx90_mpw_com.Append(CPPPATH = astrIncludePaths)
    env_netx90_mpw_com.Replace(LDFILE = 'src/netx90_com/netx90_com_intram.ld')
    src_netx90_mpw_com = env_netx90_mpw_com.SetBuildPath('targets/netx90_mpw_com', 'src', sources)
    elf_netx90_mpw_com = env_netx90_mpw_com.Elf('targets/netx90_mpw_com/netx90_mpw_com.elf', src_netx90_mpw_com + env_netx90_mpw_com['PLATFORM_LIBRARY'])
    txt_netx90_mpw_com = env_netx90_mpw_com.ObjDump('targets/netx90_mpw_com/netx90_mpw_com.txt', elf_netx90_mpw_com, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
    bb0_netx90_mpw_com = env_netx90_mpw_com.HBootImage('targets/netx90_mpw_com/netx90_mpw_com.bin', 'src/netx90_com/COM_to_INTRAM.xml', HBOOTIMAGE_KNOWN_FILES=dict({'tElfCOM': elf_netx90_mpw_com}))

if hasattr(atEnv, 'NETX90_MPW_APP') == True:
    # Blinki for the netX90 application CPU.
    env_netx90_mpw_app = atEnv.NETX90_MPW_APP.Clone()
    env_netx90_mpw_app.Append(CPPPATH = astrIncludePaths)
    env_netx90_mpw_app.Replace(LDFILE = 'src/netx90_app/netx90_app.ld')
    src_netx90_mpw_app = env_netx90_mpw_app.SetBuildPath('targets/netx90_mpw_app', 'src', sources + sources_netx90_app_additional)
    elf_netx90_mpw_app = env_netx90_mpw_app.Elf('targets/netx90_mpw_app/netx90_mpw_app.elf', src_netx90_mpw_app + env_netx90_mpw_app['PLATFORM_LIBRARY'])
    txt_netx90_mpw_app = env_netx90_mpw_app.ObjDump('targets/netx90_mpw_app/netx90_mpw_app.txt', elf_netx90_mpw_app, OBJDUMP_FLAGS=['--disassemble', '--source', '--all-headers', '--wide'])
    bin_netx90_mpw_app = env_netx90_mpw_app.ObjCopy('targets/netx90_mpw_app/netx90_mpw_app_data.bin', elf_netx90_mpw_app)
    bb0_netx90_mpw_app = env_netx90_mpw_app.IFlashImage('targets/netx90_mpw_app/netx90_mpw_app.bin', bin_netx90_mpw_app)

if hasattr(atEnv, 'NETX56') == True:
    env_netx56 = atEnv.NETX56.Clone()
    env_netx56.Append(CPPPATH = astrIncludePaths)
    env_netx56.Replace(LDFILE = 'src/netx56/netx56_intram.ld')
    src_netx56 = env_netx56.SetBuildPath('targets/netx56', 'src', sources)
    elf_netx56 = env_netx56.Elf('targets/netx56/netx56.elf', src_netx56 + env_netx56['PLATFORM_LIBRARY'])
    bb0_netx56 = env_netx56.BootBlock('targets/netx56/netx.rom', elf_netx56, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
    bb1_netx56 = env_netx56.BootBlock('targets/netx56/netx56_spi_intram.bin', elf_netx56, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

if hasattr(atEnv, 'NETX50') == True:
    env_netx50 = atEnv.NETX50.Clone()
    env_netx50.Append(CPPPATH = astrIncludePaths)
    env_netx50.Replace(LDFILE = 'src/netx50/netx50_intram.ld')
    src_netx50 = env_netx50.SetBuildPath('targets/netx50', 'src', sources)
    elf_netx50 = env_netx50.Elf('targets/netx50/netx50.elf', src_netx50 + env_netx50['PLATFORM_LIBRARY'])
    bb0_netx50 = env_netx50.BootBlock('targets/netx50/netx.rom', elf_netx50, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
    bb1_netx50 = env_netx50.BootBlock('targets/netx50/netx50_spi_intram.bin', elf_netx50, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')

if hasattr(atEnv, 'NETX10') == True:
    env_netx10 = atEnv.NETX10.Clone()
    env_netx10.Append(CPPPATH = astrIncludePaths)
    env_netx10.Replace(LDFILE = 'src/netx10/netx10_intram.ld')
    src_netx10 = env_netx10.SetBuildPath('targets/netx10', 'src', sources)
    elf_netx10 = env_netx10.Elf('targets/netx10/netx10.elf', src_netx10 + env_netx10['PLATFORM_LIBRARY'])
    bb0_netx10 = env_netx10.BootBlock('targets/netx10/netx.rom', elf_netx10, BOOTBLOCK_SRC='MMC', BOOTBLOCK_DST='INTRAM')
    bb1_netx10 = env_netx10.BootBlock('targets/netx10/netx10_spi_intram.bin', elf_netx10, BOOTBLOCK_SRC='SPI_GEN_10', BOOTBLOCK_DST='INTRAM')
