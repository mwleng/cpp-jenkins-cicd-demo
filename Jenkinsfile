pipeline {
    agent none
    options {
        timestamps()
        skipDefaultCheckout(true)
    }
    stages {
        stage('Build and test') {
            matrix {
                axes {
                    axis {
                        name 'COMPILER'
                        values 'gcc', 'clang'
                    }
                }
                agent { label 'ubuntu' }
                stages {
                    stage('Checkout') {
                        steps { checkout scm }
                    }
                    stage('Configure') {
                        steps { sh "./scripts/configure.sh build-${COMPILER} ${COMPILER}" }
                    }
                    stage('Compile') {
                        steps { sh "cmake --build build-${COMPILER} --parallel" }
                    }
                    stage('Test') {
                        steps { sh "ctest --test-dir build-${COMPILER} --output-on-failure" }
                    }
                }
            }
        }
        stage('Package') {
            agent { label 'ubuntu' }
            steps {
                checkout scm
                sh './scripts/package.sh'
                archiveArtifacts artifacts: 'dist/*', fingerprint: true
            }
        }
    }
}

