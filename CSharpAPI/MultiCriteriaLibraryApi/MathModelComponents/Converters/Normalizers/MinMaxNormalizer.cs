using System.Runtime.InteropServices;

namespace MultiCriteriaLibraryApi.MathModelComponents.Converters.Normalizers;

public class MinMaxNormalizer : INormalizer
{
    internal IntPtr _normalizerPtr;

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MinMaxNormalizer_getNormalizedMathModel(IntPtr normalizer, IntPtr mathModel);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr MinMaxNormalizer_createNormalizer();
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void MinMaxNormalizer_deleteNormalizer(IntPtr normalizer);

    public MinMaxNormalizer() => _normalizerPtr = MinMaxNormalizer_createNormalizer();
    
    ~MinMaxNormalizer() => MinMaxNormalizer_deleteNormalizer(_normalizerPtr);

    IntPtr INormalizer.getPtr()
    {
        return _normalizerPtr;
    }

    public MathModel GetNormalizedMathModel(MathModel mathModel)
    {
        IntPtr resultMathModelPtr = MinMaxNormalizer_getNormalizedMathModel(_normalizerPtr, mathModel._mathModelPtr);
        return new MathModel(resultMathModelPtr);
    }
}