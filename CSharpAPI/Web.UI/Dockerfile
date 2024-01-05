FROM mcr.microsoft.com/dotnet/aspnet:7.0 AS base
WORKDIR /app
EXPOSE 80
EXPOSE 443

FROM mcr.microsoft.com/dotnet/sdk:7.0 AS build
WORKDIR /src
COPY ["Web.UI.csproj", "."]
RUN dotnet restore "Web.UI.csproj"
COPY . .
WORKDIR "/src"
RUN dotnet build "Web.UI.csproj" -c Release -o /build

FROM build AS publish
RUN dotnet publish "Web.UI.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "Web.UI.dll"]
