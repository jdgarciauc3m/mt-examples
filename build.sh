docker build -t mt-builder .
docker run --rm -v $(pwd):/app -w /app mt-builder cmake --workflow --preset=all
docker run --rm -v $(pwd):/app -w /app mt-builder cmake --install out/build/default --prefix=out --config=Release