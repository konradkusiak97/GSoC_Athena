#include <CL/sycl.hpp>
#include <iostream>

// Matrix and vector size constant N and work group size for nd_range kernel
constexpr int N = 2048;
constexpr int wGroupSize = 16;

// Function that performs bilinear quadratic form on the CPU
auto bilinearQuad_host(int* vector, int* matrix){

    // final result variable 
    long sum = 0;

    // Perform the reduction
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            sum += matrix[i+j] * vector[i] * vector[j];
        }
    }
    return sum;
}

// Function that performs bilinear quadratic form on the device
auto bilinearQuad_device(int* vector, int* matrix, long* sum, sycl::queue Q){

    // Calculate the nd_range for the kernel
    auto range = sycl::nd_range<2>{sycl::range<2>(N,N), sycl::range<2>(wGroupSize,wGroupSize)};

    // Submit the job to the queue
    Q.submit([&](sycl::handler& h){
        
        // Execute the reduction on the device
        // Uses sycl reduction as a parameter for parallel_for
        h.parallel_for(range, sycl::reduction(sum, sycl::plus<>()), [=](sycl::nd_item<2> item, auto& sum){

            auto row = item.get_global_id(0);
            auto col = item.get_global_id(1);

            sum += vector[row] * matrix[row+col] * vector[col]; 

        });
    }).wait_and_throw();
}

int main() {

    try {
        sycl::queue Q(sycl::default_selector{});

        // Print device information
        std::cout << "Running on a device: "
                << Q.get_device().get_info<sycl::info::device::name>()
                << "\n";
        // Print the problem size 
        std::cout << "Problem size: " << N << "\n";

        // Allocate shared memory for the vector and matrix
        int* shared_vector = sycl::malloc_shared<int>(N, Q);
        int* shared_matrix = sycl::malloc_shared<int>(N*N, Q);

        // Allocate memory for the sum for the device 
        long* sum = sycl::malloc_shared<long>(1, Q);

        // Initialize the vector and matrix on the host
        for (int i = 0; i < N; ++i){
            shared_vector[i] = i;
            for (int j = 0; j < N; ++j){
                shared_matrix[i+j] = i+j;
            }
        }

        // Initialize the sum to 0
        *sum = 0;

        // Calculate the bilinear quadratic form on the host
        auto host_sum = bilinearQuad_host(shared_vector, shared_matrix);

        // Calculate the bilinear quadratic form on the device
        bilinearQuad_device(shared_vector, shared_matrix, sum, Q);
        auto device_sum = sum[0];

        // Check if the both results match
        assert(host_sum == device_sum);
        std::cout << "Success! Host and device results are the same and are equal to: " << host_sum << "\n";

        // Free the allocated resources
        free(shared_vector, Q);
        free(shared_matrix, Q);
        free(sum, Q);

    } catch (sycl::exception const& e) {
        std::cout << "Sycl exception caught!\n" << e.what();
        std::terminate();
    }

    return 0;
}
