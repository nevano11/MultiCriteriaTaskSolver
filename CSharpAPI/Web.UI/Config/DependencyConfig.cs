using MultiCriteriaLibraryApi.DecisionMakingMethod.Method.AggregationOperators;
using Web.UI.Service;

namespace Web.UI.Config;


using System.Reflection;
using Microsoft.OpenApi.Models;
using MultiCriteriaLibraryApi.CriteriaRelation.Relations;
using MultiCriteriaLibraryApi.CriteriaRelation.Relations.WeightCriteriaRelations;
using MultiCriteriaLibraryApi.DecisionMakingMethod.AbstractMultiCriteriaMethod.MultiCriteriaMethod;
using MultiCriteriaLibraryApi.DecisionMakingMethod.Method;
using MultiCriteriaLibraryApi.MathModelComponents.Converters;
using MultiCriteriaLibraryApi.MathModelComponents.Converters.Normalizers;
using Web.UI.Entity;

public static class DependencyConfig
{
    public static void ConfigureReferenceBooks(IServiceCollection serviceCollection)
    {
        serviceCollection.AddSingleton(x => new ReferenceInfo<AbstractOneStepMethod>
            {
                Name = "Одношаговый МПР",
                Values = new Dictionary<string, Type>
                {
                    { "Лексикографическая оптимизация", typeof(LexicographicOptimization) },
                    { "Метод свертки критериев", typeof(CriteriaAggregationMethod) }
                }
            }
        );
        serviceCollection.AddSingleton(x => new ReferenceInfo<AbstractMultiStepMethod>
        {
            Name = "Многошаговый МПР",
            Values = new Dictionary<string, Type>
            {
                { "Метод последовательных уступок", typeof(SuccessiveConcessionsMethod) }
            }
        });
        serviceCollection.AddSingleton(x => new ReferenceInfo<INormalizer> {
                Name = "Нормировщик",
                Values = new Dictionary<string, Type>
                {
                    { "Минимаксный нормировщик", typeof(MinMaxNormalizer) }
                }
            }
        );
        serviceCollection.AddSingleton(x => new ReferenceInfo<AbstractAggregationOperator> {
            Name = "Оператор свёртки",
            Values = new Dictionary<string, Type>
            {
                { "Аддитивная свёртка", typeof(AddictiveAggregationOperator) },
                { "Мультипликативная свёртка", typeof(MultiplicativeAggregationOperator) },
                { "Свёртка расстояния до идеала", typeof(IdealDistanceAggregationOperator) }
            }
        });
        serviceCollection.AddSingleton(x => new ReferenceInfo<ICriteriaRelation>
        {
            Name = "Отношения критериев",
            Values = new Dictionary<string, Type>
            {
                { "Лексикографическое отношение", typeof(AllCriteriaRelation) },
                { "Простое ранжирование", typeof(SimpleRankingMethod) },
                { "Пропорциональный метод", typeof(ProportionalMethod) },
                { "Порядковая информация" ,typeof(SimpleCriteriaRelation) }
            }
        });
        serviceCollection.AddSingleton(x => new SupportedMethodInfo
            {
                OneStepMethodInfo = new Dictionary<string, Dictionary<string, List<string>>>
                {
                    { "Лексикографическая оптимизация", new Dictionary<string, List<string>>()},
                    { "Метод свертки критериев", new Dictionary<string, List<string>>
                        {
                            { "Оператор свёртки", new List<string> {"Аддитивная свёртка", "Мультипликативная свёртка", "Свёртка расстояния до идеала"} },
                            { "Нормировщик", new List<string> {"Минимаксный нормировщик"} }
                        }
                    }
                },
                MultiStepMethodInfo = new Dictionary<string, Dictionary<string, List<string>>>
                {
                    { "Метод последовательных уступок", new Dictionary<string, List<string>>()}
                }
            }
        );
        serviceCollection.AddSingleton(x => new MultiStepResultStorage());
    }
    public static void ConfigureSwagger(IServiceCollection services)
    {
        // Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
        services.AddEndpointsApiExplorer();
        services.AddSwaggerGen(options =>
        {
            
            options.SwaggerDoc("v1", new OpenApiInfo
            {
                Version = "v1",
                Title = "Inspection API",
                Description = "An ASP.NET Core Web API for managing inspections",
                Contact = new OpenApiContact
                {
                    Name = "RiskProf",
                    Url = new Uri("https://riskprof.ru/")
                }
            });
            
            string xmlFilename = $"{Assembly.GetExecutingAssembly().GetName().Name}.xml";
            options.IncludeXmlComments(Path.Combine(AppContext.BaseDirectory, xmlFilename));
        });
    }
}