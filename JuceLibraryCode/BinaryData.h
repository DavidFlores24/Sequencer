/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Clap_wav;
    const int            Clap_wavSize = 33924;

    extern const char*   HiHat_wav;
    const int            HiHat_wavSize = 24076;

    extern const char*   Kick_wav;
    const int            Kick_wavSize = 50952;

    extern const char*   Snare_wav;
    const int            Snare_wavSize = 34572;

    extern const char*   a_wav;
    const int            a_wavSize = 182224;

    extern const char*   b_wav;
    const int            b_wavSize = 165104;

    extern const char*   c_wav;
    const int            c_wavSize = 189772;

    extern const char*   d_wav;
    const int            d_wavSize = 160410;

    extern const char*   e_wav;
    const int            e_wavSize = 140708;

    extern const char*   e2_wav;
    const int            e2_wavSize = 62744;

    extern const char*   fSharp_wav;
    const int            fSharp_wavSize = 141814;

    extern const char*   g_wav;
    const int            g_wavSize = 163816;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 12;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
