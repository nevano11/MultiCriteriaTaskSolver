using System.Runtime.InteropServices;

namespace MultiCriteriaLibraryApi.MathModelComponents.Components;

public class EstimateVector
{
    internal IntPtr _estimateVectorPtr { get; }

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr EstimateVector_new(int id, IntPtr name, int nameLength, IntPtr markArray, int criteriaCount);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr EstimateVector_new_copy(IntPtr other);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void EstimateVector_delete(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int EstimateVector_getId(IntPtr obj);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr EstimateVector_getName(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr EstimateVector_getMarks(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int EstimateVector_getCriteriaCount(IntPtr obj);

    public EstimateVector(int id, string name, double[] markArray, int criteriaCount)
    {
        IntPtr namePtr = Marshal.StringToHGlobalAnsi(name);
        
        int size = criteriaCount * sizeof(double);
        IntPtr marksPtr = Marshal.AllocHGlobal(size);
        Marshal.Copy(markArray, 0, marksPtr, criteriaCount);
        
        _estimateVectorPtr = EstimateVector_new(
            id, namePtr, name.Length, marksPtr, criteriaCount);
        Marshal.FreeHGlobal(namePtr);
        Marshal.FreeHGlobal(marksPtr);
    }

    public EstimateVector(EstimateVector other)
    {
        _estimateVectorPtr = EstimateVector_new_copy(other._estimateVectorPtr);
    }
    
    internal EstimateVector(IntPtr other)
    {
        _estimateVectorPtr = other;
    }

    ~EstimateVector()
    {
        EstimateVector_delete(_estimateVectorPtr);
    }

    public int Id => EstimateVector_getId(_estimateVectorPtr);

    public string Name => Marshal.PtrToStringAnsi(EstimateVector_getName(_estimateVectorPtr));

    public double[] Marks
    {
        get
        {
            int criteriaCount = EstimateVector_getCriteriaCount(_estimateVectorPtr);
            double[] marks = new double[criteriaCount];
            Marshal.Copy(EstimateVector_getMarks(_estimateVectorPtr), marks, 0, criteriaCount);
            return marks;
        }
    }

    public int CriteriaCount => EstimateVector_getCriteriaCount(_estimateVectorPtr);

    public override string ToString()
    {
        string marksStr = "[";
        int cc = CriteriaCount;
        for (int i = 0; i < cc; i++)
        {
            marksStr += Marks[i];
            if (i != cc - 1)
            {
                marksStr += ", ";
            }
        }
        marksStr += "]";
        return $"EstimateVector: id={Id}, name={Name}, criteriaCount={cc}, marks={marksStr}";
    }
}
