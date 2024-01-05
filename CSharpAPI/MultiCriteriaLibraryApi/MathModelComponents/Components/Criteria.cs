using System.Runtime.InteropServices;

namespace MultiCriteriaLibraryApi.MathModelComponents.Components;

public enum CriteriaType
{
    MAXIMIZATION,
    MINIMIZATION
}

public class Criteria
{
    internal IntPtr _criteriaPtr { get; }

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr Criteria_new(int id, IntPtr name, int nameLength, int criteriaType);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr Criteria_new_copy(IntPtr other);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern void Criteria_delete(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int Criteria_getId(IntPtr obj);
    
    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern IntPtr Criteria_getName(IntPtr obj);

    [DllImport("libMultiCriteriaDecisionMakingLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
    private static extern int GetCriteriaType(IntPtr obj);

    public Criteria(int id, string name, CriteriaType criteriaType = CriteriaType.MAXIMIZATION)
    {
        IntPtr namePtr = Marshal.StringToHGlobalAnsi(name);
        _criteriaPtr = Criteria_new(id, 
            namePtr,
            name.Length,
            criteriaType == CriteriaType.MAXIMIZATION ? 1 : 0);
        Marshal.FreeHGlobal(namePtr);
    }

    public Criteria(Criteria other)
    {
        _criteriaPtr = Criteria_new_copy(other._criteriaPtr);
    }
    
    internal Criteria(IntPtr other)
    {
        _criteriaPtr = other;
    }

    ~Criteria()
    {
        Criteria_delete(_criteriaPtr);
    }

    public int Id => Criteria_getId(_criteriaPtr);

    public string Name
    {
        get
        {
            var a = Criteria_getName(_criteriaPtr);
            var marshRes = Marshal.PtrToStringAnsi(a);
            return marshRes;
        }
    }

    public CriteriaType Type
    {
        get
        {
            var r = GetCriteriaType(_criteriaPtr);
            return r == 1 ? CriteriaType.MAXIMIZATION : CriteriaType.MINIMIZATION;
        }
    }

    public override string ToString()
    {
        return $"Criteria: id={Id}, name={Name}, type={(Type == CriteriaType.MAXIMIZATION ? "max" : "min")}";
    }
}